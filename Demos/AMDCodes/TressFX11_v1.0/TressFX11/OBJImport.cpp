//--------------------------------------------------------------------------------------
// File: OBJImport.cpp
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "..\\DXUT\\Core\\DXUT.h"
#include "OBJImport.h"
#include "..\\DXUT\\Optional\\SDKmisc.h"

COBJImport::COBJImport(void)
{
	this->m_bHasNormal = false;
}

COBJImport::~COBJImport(void)
{
}

void COBJImport::BuildMesh()
{
    // Group the model's triangles based on material type.
	vector<vector<UINT>> subMeshes;
	subMeshes.resize(m_Materials.size());

    // Reorder all the triangles according to material id.
    for (UINT i = 0; i < static_cast<int>(m_AttributeBuffer.size()); ++i)
    {
        int materialId = m_AttributeBuffer[i];
		subMeshes[materialId].push_back(i);
    }

	// Reorder index buffer and attribute buffer according to material id
	vector<UINT> indexBuffer;
	indexBuffer.reserve(m_IndexBuffer.size());
	
	m_Subsets.resize(m_Materials.size());
	Subset* pSubset = NULL;
	int triangleID = 0;
	for(UINT i=0; i<subMeshes.size(); i++)
	{
		pSubset = &m_Subsets[i];
		pSubset->materialID = i;
		pSubset->startIndex = triangleID*3;
		pSubset->triangleCount = subMeshes[i].size();

		for(UINT j=0; j<subMeshes[i].size(); j++)
		{
			indexBuffer.push_back(m_IndexBuffer[subMeshes[i][j]*3]);
			indexBuffer.push_back(m_IndexBuffer[subMeshes[i][j]*3+1]);
			indexBuffer.push_back(m_IndexBuffer[subMeshes[i][j]*3+2]);
			m_AttributeBuffer[triangleID] = i;
			triangleID++;
		}
	}

	m_IndexBuffer.swap(indexBuffer);
	indexBuffer.clear();
	subMeshes.clear();
}

void COBJImport::UpdateBoundingSphere()
{
	BBox bBox;

	for(UINT i=0; i<this->m_VertexBuffer.size(); i++)
	{
		StandardVertex* pVertex = &m_VertexBuffer[i];
		bBox = Union(bBox, Float3(pVertex->position));
	}
	
	Float3 c; float radius;
	bBox.BoundingSphere(&c, &radius);
	m_bSphere.center = D3DXVECTOR3(c.x, c.y, c.z);
	m_bSphere.radius = radius;

}


void COBJImport::ScaleRotateTranslate(D3DXVECTOR3 scale, D3DXVECTOR3 rotation, D3DXVECTOR3 translation)
{
	// translation
	for(UINT i=0; i<this->m_VertexBuffer.size(); i++)
	{
		StandardVertex* pVertex = &m_VertexBuffer[i];

		// scale
		pVertex->position.x *= scale.x;
		pVertex->position.y *= scale.y;
		pVertex->position.z *= scale.z;

		// rotation
		D3DXMATRIX rotateMat;
		D3DXMatrixRotationYawPitchRoll(&rotateMat, rotation.y, rotation.x, rotation.z);

		D3DXVECTOR3 temp;
		D3DXVec3TransformCoord(&temp, &(pVertex->position), &rotateMat);
		pVertex->position = temp;
		
		D3DXVec3TransformNormal(&temp, &(pVertex->normal), &rotateMat);
		pVertex->normal = temp;

		// translation
		pVertex->position += translation;
	}

	UpdateBoundingSphere();
}

// For each vertex, accumulate normal value in all its connecting triangles and then average
void COBJImport::GenerateNormal()
{
	int numVertices = this->m_VertexBuffer.size();
	int numTriangles = this->m_IndexBuffer.size()/3;

	vector<float> weight;
	weight.resize(numVertices, 0);

	for(int i=0; i<numTriangles; i++)
	{
		// get the three vertices in a triangle
		int id0 = m_IndexBuffer[i*3+0];
		int id1 = m_IndexBuffer[i*3+1];
		int id2 = m_IndexBuffer[i*3+2];

		D3DXVECTOR3 v21 = m_VertexBuffer[id2].position - m_VertexBuffer[id1].position;
		D3DXVECTOR3 v01 = m_VertexBuffer[id0].position - m_VertexBuffer[id1].position;

		D3DXVECTOR3 normal;
		D3DXVec3Cross(&normal, &v21, &v01);
		D3DXVec3Normalize(&normal, &normal);

		m_VertexBuffer[id0].normal += normal;		weight[id0] += 1;
		m_VertexBuffer[id1].normal += normal;		weight[id1] += 1;
		m_VertexBuffer[id2].normal += normal;		weight[id2] += 1;

		
	}
	for(int i=0; i<numVertices; i++)
	{
		D3DXVECTOR3 v = m_VertexBuffer[i].normal / weight[i];
		D3DXVec3Normalize(&v, &v);
		m_VertexBuffer[i].normal = v;
	}
}

HRESULT COBJImport::LoadModelFromOBJ( const WCHAR* strFileName )
{
	
    WCHAR strMaterialFilename[MAX_PATH] = {0};	// for storing .mtl file name
    char str[MAX_PATH];		//char vertion of directory for setting up file stream
    HRESULT hr;

    // Find the file
    WideCharToMultiByte( CP_ACP, 0, strFileName, -1, str, MAX_PATH, NULL, NULL );

    // Store the directory where the mesh was found
    wcscpy_s( m_strMediaDir, MAX_PATH - 1, strFileName );
    WCHAR* pch = wcsrchr( m_strMediaDir, L'\\' );
    
	if( pch )
        *pch = NULL;

    // Create temporary storage for the input data. Once the data has been loaded into
    // a reasonable format we can create a D3DXMesh object and load it with the mesh data.
    vector<D3DXVECTOR3> Positions;
    vector<D3DXVECTOR2> TexCoords;
    vector<D3DXVECTOR3> Normals;

    // The first subset uses the default material
    Material* pMaterial = new Material();
    if( pMaterial == NULL )
        return E_OUTOFMEMORY;

    wcscpy_s( pMaterial->strName, MAX_PATH - 1, L"default" );
	m_Materials.push_back( *pMaterial );
	SAFE_DELETE(pMaterial);

    DWORD dwCurSubset = 0;

    // File input
    WCHAR strCommand[MAX_PATH] = {0};
    wifstream InFile( str );
    if( !InFile )
		::MessageBoxA(0, "OBJ file does not exsit", "Error", 0);

	WCHAR strData[MAX_PATH]={0};
	WCHAR wspace[] = L" \t";

	while(!InFile.eof())
    {
		if(!InFile)
		{
			::MessageBox(0, L"Input file string error, not reaching end yet", L"Error", 0);		
			break;
		}		

        InFile >> strCommand;
        if( 0 == wcscmp( strCommand, L"#" ) )
        {
			// Comment, skip this line
        }
        else if( 0 == wcscmp( strCommand, L"v" ) )
        {
            // Vertex Position, get the rest of the line and parse them
			InFile.get(strData, MAX_PATH);
            
			float x = (float)_wtof( wcstok( strData, wspace ) );
            float y = (float)_wtof( wcstok( NULL, wspace ) );
            float z = (float)_wtof( wcstok( NULL, wspace ) ); 
			Positions.push_back( D3DXVECTOR3( x, y, z ) );
        }
        else if( 0 == wcscmp( strCommand, L"vt" ) )
        {
            // Vertex TexCoord, get the rest of the line and parse them
 			InFile.get(strData, MAX_PATH);
           
			// Note in OpenGL, the texcoord start from the bottom left while dx start from upper left
			// You might need to flip if the original coordinate start from bottom left
			float u = (float)_wtof( wcstok( strData, wspace ) );
            float v = 1.f - (float)_wtof( wcstok( NULL, wspace ) ); // flip coordinate
			TexCoords.push_back( D3DXVECTOR2( u, v ) );
        }
        else if( 0 == wcscmp( strCommand, L"vn" ) )
        {
            // Vertex Normal, get the rest of the line and parse
 			InFile.get(strData, MAX_PATH);

			float x = (float)_wtof( wcstok( strData, wspace) );
            float y = (float)_wtof( wcstok( NULL, wspace ) );
            float z = (float)_wtof( wcstok( NULL, wspace ) ); 
			Normals.push_back( D3DXVECTOR3( x, y, z ) );
        }
        else if( 0 == wcscmp( strCommand, L"f" ) )
        {
            // obtain the polygon information
			// Obj requires at least 3 vertices to form a face 
			// Here we first get 3 vertices to form the 1st triangle
			// then we loop for more vertices and create triangle accordingly
			UINT iPosition, iTexCoord, iNormal;
			UINT index[3];
            StandardVertex vertex;

			// The first three vertices form a triangle(0, 1, 2)
            for( UINT iFace = 0; iFace < 3; iFace++ )
            {
                ZeroMemory( &vertex, sizeof( StandardVertex ) );

                // OBJ format uses 1-based arrays
                InFile >> iPosition;
                vertex.position = Positions[ iPosition - 1 ];

                if( '/' == InFile.peek() )
                {
                    InFile.ignore();

					// check if texcoord present
                    if( '/' != InFile.peek() )
                    {
                        // Optional texture coordinate
                        InFile >> iTexCoord;
                        vertex.texcoord = TexCoords[ iTexCoord - 1 ];
                    }

					// then check if normal present
                    if( '/' == InFile.peek() )
                    {
						m_bHasNormal = true;
                        InFile.ignore();
                        // Optional vertex normal
                        InFile >> iNormal;
                        vertex.normal = Normals[ iNormal - 1 ];
                    }
                }

                // If a duplicate vertex doesn't exist, add this vertex to the Vertices
                // list. Store the index in the Indices array. The Vertices and Indices
                // lists will eventually become the Vertex Buffer and Index Buffer for
                // the mesh.
                index[iFace] = AddVertex( iPosition, &vertex );
				m_IndexBuffer.push_back( index[iFace] );
            }
			m_AttributeBuffer.push_back( dwCurSubset );

			// If the more than 3 vertices exist, we form more triangles to complete the polygon
			// first check if we reach the end of file or line
			if(!InFile.eof() && '\n' != InFile.peek())
			{
				InFile.get(strData, MAX_PATH);
				WCHAR* pch;
				pch = wcstok (strData, L" ");
				while(pch != NULL)
				{
					iTexCoord = 0; iNormal = 0;
					//check if we could find out the information of fourth vertex
					if (swscanf_s(pch, L"%d/%d/%d", &iPosition, &iTexCoord, &iNormal)>0) // for cases: v v/vt v/vt/vn
					{
						if(wcsstr(pch, L"//")) // for case: v//vn
						{
							swscanf_s(pch, L"%d//%d", &iPosition, &iNormal);
						}
						ZeroMemory( &vertex, sizeof( StandardVertex ) );

						vertex.position = Positions[ iPosition - 1 ];
						
						if(iTexCoord>0 && iTexCoord<=TexCoords.size()) // safty check since texcoord is optional
							vertex.texcoord = TexCoords[ iTexCoord - 1 ];
						
						if (iNormal>0 && iNormal<=Normals.size())
							vertex.normal = Normals[ iNormal - 1 ];

						// Always connet the first vertex with the last two vertices 
						// to form the new triangle
						index[1] = index[2];
						index[2] = AddVertex( iPosition, &vertex );

						// add the triangle
						m_IndexBuffer.push_back( index[0] );
						m_IndexBuffer.push_back( index[1] );
						m_IndexBuffer.push_back( index[2] );
						m_AttributeBuffer.push_back( dwCurSubset );
					}
					pch = wcstok (NULL, L" ");
				}
			}
		}
        else if( 0 == wcscmp( strCommand, L"mtllib" ) )
        {
            // Material library
            InFile >> strMaterialFilename;
        }
        else if( 0 == wcscmp( strCommand, L"usemtl" ) )
        {
            // Material
            WCHAR strName[MAX_PATH] = {0};
            InFile >> strName;

            bool bFound = false;
			for( UINT iMaterial = 0; iMaterial < m_Materials.size(); iMaterial++ )
            {
                Material* pCurMaterial = &m_Materials[iMaterial];
                if( 0 == wcscmp( pCurMaterial->strName, strName ) )
                {
                    bFound = true;
                    dwCurSubset = iMaterial;
                    break;
                }
            }

            if( !bFound )
            {
                pMaterial = new Material();
                if( pMaterial == NULL )
                    return E_OUTOFMEMORY;

				dwCurSubset = m_Materials.size();

                wcscpy_s( pMaterial->strName, MAX_PATH - 1, strName );

				m_Materials.push_back( *pMaterial );
				SAFE_DELETE(pMaterial);
            }
        }
        else
        {
            // Unimplemented or unrecognized command
        }

		// we're not interested in the rest of the line, so skip them
		InFile.ignore( MAX_PATH, L'\n' );
    }

    // Cleanup
    InFile.close();

	// Generate vertex normal if required
	if(!m_bHasNormal)
		GenerateNormal();

	// Calculate bounding sphere;
	UpdateBoundingSphere();

    // If an associated material file was found, read that in as well.
    if( strMaterialFilename[0] )
    {
        V_RETURN( LoadMaterialsFromMTL( strMaterialFilename ) );
    }
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
UINT COBJImport::AddVertex( UINT hash, StandardVertex* pVertex )
{
    UINT index = 0;
    std::map<UINT, std::vector<UINT> >::const_iterator iter = m_VertexCache.find(hash);

    if (iter == m_VertexCache.end())
    {
        // Vertex hash doesn't exist in the cache.
        index = static_cast<UINT>(m_VertexBuffer.size());
        m_VertexBuffer.push_back(*pVertex);
        m_VertexCache.insert(std::make_pair(hash, std::vector<UINT>(1, index)));
    }
    else
    {
        // One or more vertices have been hashed to this entry in the cache.
        const std::vector<UINT> &vertices = iter->second;
        const StandardVertex *pCachedVertex = 0;
        bool found = false;

        for (std::vector<UINT>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        {
            index = *i;
            pCachedVertex = &m_VertexBuffer[index];

            if (memcmp(pCachedVertex, pVertex, sizeof(StandardVertex)) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            index = static_cast<UINT>(m_VertexBuffer.size());
            m_VertexBuffer.push_back(*pVertex);
            m_VertexCache[hash].push_back(index);
        }
    }

    return index;
}


////////////////////////////////////////////////////////////////////////////////////////
HRESULT COBJImport::LoadMaterialsFromMTL( const WCHAR* strFileName )
{
    // Set the current directory based on where the mesh was found
    WCHAR wstrOldDir[MAX_PATH] = {0};
    GetCurrentDirectory( MAX_PATH, wstrOldDir );
    SetCurrentDirectory( m_strMediaDir );

    // Find the file
    char cstrPath[MAX_PATH];
    WideCharToMultiByte( CP_ACP, 0, strFileName, -1, cstrPath, MAX_PATH, NULL, NULL );

    // File input
    WCHAR strCommand[256] = {0};

    wifstream InFile( cstrPath );
    if( !InFile )
        return DXTRACE_ERR( L"wifstream::open", E_FAIL );

    // Restore the original current directory
    SetCurrentDirectory( wstrOldDir );

    Material* pMaterial = NULL;

    for(; ; )
    {
        InFile >> strCommand;
        if( !InFile )
            break;

        if( 0 == wcscmp( strCommand, L"newmtl" ) )
        {
            // Switching active materials
            WCHAR strName[MAX_PATH] = {0};
            InFile >> strName;

            pMaterial = NULL;
			for( UINT i = 0; i < m_Materials.size(); i++ )
            {
                Material* pCurMaterial = &(m_Materials[i]);
                if( 0 == wcscmp( pCurMaterial->strName, strName ) )
                {
                    pMaterial = pCurMaterial;
                    break;
                }
            }
        }

        // The rest of the commands rely on an active material
        if( pMaterial == NULL )
		{
	        InFile.ignore( MAX_PATH, L'\n' );
            continue;
		}
        if( 0 == wcscmp( strCommand, L"#" ) )
        {
            // Comment
        }
        else if( 0 == wcscmp( strCommand, L"Ka" ) )
        {
            // Ambient color
            float r, g, b;
            InFile >> r >> g >> b;
            pMaterial->vAmbient = D3DXVECTOR3( r, g, b );
        }
        else if( 0 == wcscmp( strCommand, L"Kd" ) )
        {
            // Diffuse color
            float r, g, b;
            InFile >> r >> g >> b;
            pMaterial->vDiffuse = D3DXVECTOR3( r, g, b );
        }
        else if( 0 == wcscmp( strCommand, L"Ks" ) )
        {
            // Specular color
            float r, g, b;
            InFile >> r >> g >> b;
            pMaterial->vSpecular = D3DXVECTOR3( r, g, b );
        }
        else if( 0 == wcscmp( strCommand, L"d" ) ||
                 0 == wcscmp( strCommand, L"Tr" ) )
        {
            // Alpha
            InFile >> pMaterial->fAlpha;
        }
        else if( 0 == wcscmp( strCommand, L"Ns" ) )
        {
            // Shininess
            int nShininess;
            InFile >> nShininess;
            pMaterial->nShininess = nShininess;
        }
        else if( 0 == wcscmp( strCommand, L"illum" ) )
        {
            // Specular on/off
            int illumination;
            InFile >> illumination;
            pMaterial->bSpecular = ( illumination == 2 );
        }
        else if( 0 == wcscmp( strCommand, L"map_Kd" ) )
        {
            // Texture
			InFile >> pMaterial->strTexture;
        }

        else
        {
            // Unimplemented or unrecognized command
        }

        InFile.ignore( MAX_PATH, L'\n' );
    }

    InFile.close();

    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////
// clear all memory and reset members
void COBJImport::Destroy()
{
	this->m_bHasNormal = false;

	std::vector<Subset>().swap(m_Subsets);			// all the sub meshes, each with different material property
	std::vector<Material>().swap(m_Materials);
	std::vector<UINT>().swap(m_IndexBuffer);
	std::vector<StandardVertex>().swap(m_VertexBuffer);
	std::vector<UINT>().swap(m_AttributeBuffer);

	std::map<UINT, std::vector<UINT>>().swap(m_VertexCache);
}
