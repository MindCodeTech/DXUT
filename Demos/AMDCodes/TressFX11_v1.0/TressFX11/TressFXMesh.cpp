//--------------------------------------------------------------------------------------
// File: TressFXMesh.cpp
//
// Hair mesh code
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "..\\DXUT\\Core\\dxut.h"
#include "TressFXMesh.h"

#include <fstream>
using namespace std;


CDX11TressFXHairMesh::CDX11TressFXHairMesh(void)
{
}

CDX11TressFXHairMesh::~CDX11TressFXHairMesh(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate the tangent value for each vertices of the strand
void CDX11TressFXHairMesh::ComputeStrandTangent(vector<StrandVertex>& strand)
{
    int numVertices = strand.size();

    // Calculate the tangent value for the first vertex of the strand 
    D3DXVECTOR3 tangent = strand[1].position - strand[0].position;
    D3DXVec3Normalize(&tangent, &tangent);
    strand[0].tangent = tangent;
    
    for (int vertex = 1; vertex < numVertices-1; vertex++) 
    {
        D3DXVECTOR3 tangent_pre = strand[vertex].position - strand[vertex-1].position;
        D3DXVec3Normalize(&tangent_pre, &tangent_pre);

        D3DXVECTOR3 tangent_next = strand[vertex+1].position - strand[vertex].position;
        D3DXVec3Normalize(&tangent_next, &tangent_next);

        tangent = tangent_pre + tangent_next;
        D3DXVec3Normalize(&tangent, &tangent);

        strand[vertex].tangent = tangent;
    }

    // Calculate the tangent value for the last vertex of the strand 
    tangent = strand[numVertices-1].position - strand[numVertices-2].position;
    D3DXVec3Normalize(&tangent, &tangent);
    strand[numVertices-1].tangent = tangent;
}

float CDX11TressFXHairMesh::ComputeStrandTexcoordZ(vector<StrandVertex>& strand)
{
    int numVertices = strand.size();
    float strandLength = 0;
    strand[0].texcoord.z = 0;
    for (int i=1; i<numVertices; i++)
    {
        D3DXVECTOR3 vec = strand[i].position - strand[i-1].position;
        float disSeg = D3DXVec3Length(&vec);
        strand[i].texcoord.z = strand[i-1].texcoord.z + disSeg;
        strandLength += disSeg;
    }
    for (int i=0; i<numVertices; i++)
    {
        strand[i].texcoord.z /= strandLength;
    }

    return strandLength;
}

void CDX11TressFXHairMesh::ScaleRotateTranslate(float scale, 
                                            D3DXVECTOR3 rotation, 
                                            D3DXVECTOR3 translation)
{
    // Scale, rotate, translate and calculate bounding box and sphere
    BBox bBox;

    // Translation
    for(int i=0;i<int(m_AMDHairSim.m_HairAssetLoader.GetHairs().size());i++)
    {
        std::vector<CHairVertex>& vertices = m_AMDHairSim.m_HairAssetLoader.GetHairs().at(i)->GetVertexArray();

        for ( int j = 0; j < (int)vertices.size(); j++ )
        {

            StrandVertex* pVertex = &(m_AMDHairSim.m_HairStrands[i][j]);

            // scale
            pVertex->position *= scale;

            // rotation
            D3DXMATRIX rotateMat;
            D3DXMatrixRotationYawPitchRoll(&rotateMat, rotation.y, rotation.x, rotation.z);

            D3DXVECTOR3 temp;
            D3DXVec3TransformCoord(&temp, &(pVertex->position), &rotateMat);
            pVertex->position = temp;
            
            D3DXVec3TransformNormal(&temp, &(pVertex->tangent), &rotateMat);
            pVertex->tangent = temp;

            // translation
            pVertex->position += translation;
            bBox = Union(bBox, Float3(pVertex->position));
        }
    }
        
    Float3 c; float radius;
    bBox.BoundingSphere(&c, &radius);
    m_bSphere.center = D3DXVECTOR3(c.x, c.y, c.z);
    m_bSphere.radius = radius;
}

void CDX11TressFXHairMesh::CreateHairMeshFromFile(ID3D11Device* pd3dDevice, 
                            float scale, 
                            D3DXVECTOR3 rotation, 
                            D3DXVECTOR3 translation)
{
    m_AMDHairSim.OnCreateDevice(pd3dDevice);
    ScaleRotateTranslate(scale, rotation, translation);
}

void CDX11TressFXHairMesh::OnFrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, float fElapsedTime, const CVector3D & windDir, float windMag)
{
    m_AMDHairSim.Simulate(pd3dDevice, pd3dContext, fElapsedTime, windDir, windMag);
}

void CDX11TressFXHairMesh::OnDestroy()
{
    m_AMDHairSim.OnDestroy();
}
