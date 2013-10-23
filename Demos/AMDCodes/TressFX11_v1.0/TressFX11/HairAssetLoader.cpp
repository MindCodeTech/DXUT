//--------------------------------------------------------------------------------------
// File: HairAssetLoader.cpp
//
// File for loading the hair assets 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "HairAssetLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "StringTokenizer.h"

using namespace std;


CHairAsset::CHairAsset(void)
{
   
}

CHairAsset::~CHairAsset(void)
{
    Clear();
}

void CHairAsset::Clear()
{
    m_VertexArray.clear();
}

void CHairAsset::ConstructAsset()
{   
    // reference vector
    for ( int i = 1; i < (int)m_VertexArray.size()-1; i++ )
    {
        CHairVertex& vert_i_minus_1 = m_VertexArray[i-1];
        CHairVertex& vert_i = m_VertexArray[i];
        CHairVertex& vert_i_plus_1 = m_VertexArray[i+1];

        // arbitrary vector
        CVector3D a(1.0f, 0, 0);

        CVector3D X_i = (vert_i.m_Pos - vert_i_minus_1.m_Pos);
        CVector3D X_i_plus_one = (vert_i_plus_1.m_Pos - vert_i.m_Pos);

        CVector3D X_i_norm = X_i.NormalizeOther();

        vert_i.m_XVec = X_i_norm;

        CVector3D Z_i = X_i.Cross(a);

        if ( Z_i.LengthSqr() < 0.0001 )
        {
            // another arbitrary vector
            a.Set(0, 1.0f, 0);
            Z_i = X_i_norm.Cross(a);
        }

        Z_i.Normalize();

        vert_i.m_ZVec = Z_i;

        CVector3D Y_i = Z_i.Cross(X_i_norm).Normalize();

        // reference vector
        vert_i.m_RefVecInLocalFrame = X_i_plus_one;

        CMatrix33 rot;

        rot(0, 0) = X_i_norm.m_X;	rot(0, 1) = Y_i.m_X;	rot(0, 2) = Z_i.m_X;
        rot(1, 0) = X_i_norm.m_Y;	rot(1, 1) = Y_i.m_Y;	rot(1, 2) = Z_i.m_Y;
        rot(2, 0) = X_i_norm.m_Z;	rot(2, 1) = Y_i.m_Z;	rot(2, 2) = Z_i.m_Z;

        rot.Transpose(); // inverse it. 

        vert_i.m_RefVecInLocalFrame = rot * vert_i.m_RefVecInLocalFrame;
    }

    InitGlobalLocalFrame();
}


void CHairAsset::InitGlobalLocalFrame()
{
    // vertex 0
    {
        CHairVertex& vert_i = m_VertexArray[0];
        CHairVertex& vert_i_plus_1 = m_VertexArray[1];

        const CVector3D vec = vert_i_plus_1.m_Pos - vert_i.m_Pos;
        CVector3D vecX = vec.NormalizeOther();

        CVector3D vecZ = vecX.Cross(CVector3D(1.0, 0, 0));

        if ( vecZ.LengthSqr() < 0.0001 )
        {
            vecZ = vecX.Cross(CVector3D(0, 1.0f, 0));
        }

        vecZ.Normalize();
        CVector3D vecY = vecZ.Cross(vecX).Normalize();

        CMatrix33 rotL2W;

        rotL2W(0, 0) = vecX.m_X;	rotL2W(0, 1) = vecY.m_X;		rotL2W(0, 2) = vecZ.m_X;
        rotL2W(1, 0) = vecX.m_Y;	rotL2W(1, 1) = vecY.m_Y;		rotL2W(1, 2) = vecZ.m_Y;
        rotL2W(2, 0) = vecX.m_Z;	rotL2W(2, 1) = vecY.m_Z;		rotL2W(2, 2) = vecZ.m_Z;

        vert_i.m_LocalTransform.GetRotation() = rotL2W;
        vert_i.m_LocalTransform.GetTranslation() = vert_i.m_Pos;
        vert_i.m_GlobalTransform = vert_i.m_LocalTransform; // For vertex 0, local and global transforms are the same. 
    }

    // vertex 1 through n-1
    for (int i = 1 ; i < (int)m_VertexArray.size(); i++ )
    {
        CHairVertex& vert_i_minus_1 = m_VertexArray[i-1];
        CHairVertex& vert_i = m_VertexArray[i];
        
        CVector3D vec = vert_i.m_Pos - vert_i_minus_1.m_Pos;
        vec = vert_i_minus_1.m_GlobalTransform.GetRotation().InverseOther() * vec;

        CVector3D vecX = vec.NormalizeOther();
    
        CVector3D X = CVector3D(1.0f, 0, 0);
        CVector3D rotAxis = X.Cross(vecX);
        float angle = acos(X.Dot(vecX));

        if ( abs(angle) < 0.001 || rotAxis.LengthSqr() < 0.001 )
        {
            vert_i.m_LocalTransform.GetRotation().SetIdentity();
        }
        else
        {
            rotAxis.Normalize();
            CQuaternion rot = CQuaternion(rotAxis, angle);
            vert_i.m_LocalTransform.GetRotation() = rot;
        }

        vert_i.m_LocalTransform.GetTranslation() = vec;
        vert_i.m_GlobalTransform = vert_i_minus_1.m_GlobalTransform * vert_i.m_LocalTransform;
        vert_i.m_OrgPosInLocalFrame_i_minus_1 = vert_i.m_LocalTransform.GetTranslation();
    }

    for (int i = 0 ; i < (int)m_VertexArray.size(); i++ )
    {
        CHairVertex& vert = m_VertexArray[i];

        CVector3D x(1.0f, 0.0f, 0.0f);
        CVector3D y(0.0f, 1.0f, 0.0f);
        CVector3D z(0.0f, 0.0f, 1.0f);
        
        x = vert.m_GlobalTransform * x;
        y = vert.m_GlobalTransform * y;
        z = vert.m_GlobalTransform * z;

        vert.m_XVec = x - vert.m_Pos;
        vert.m_ZVec = z - vert.m_Pos;
    }
}

CHairAssetLoader::CHairAssetLoader(void) 
{
}

CHairAssetLoader::~CHairAssetLoader(void)
{
    Clear();
}

bool CHairAssetLoader::LoadAppend(const char* filename, int groupId, bool bMovable, int maxNumOfVerticesInStrand/* = 32*/)
{
    ifstream inFile(filename);
    string sLine;
    vector<string> sTokens;

    if ( !inFile.is_open() )
        return false;

    getline(inFile, sLine);
    sTokens.clear(); 
    int numFound = StringTokenizer(sLine, string(" "), sTokens, false);

    if ( numFound == 0 )
        return false;

    // numStrands
    int numStrands = 0;

    vector <string>::iterator iter;
    string sToken; 

    iter = sTokens.begin();
    sToken = *(iter);

    assert(sToken == "numStrands");

    ++iter;
    sToken = *(iter);

    numStrands = atoi(sToken.c_str());
    
    getline(inFile, sLine); // is sorted 1

    for ( int strand = 0; strand < numStrands; strand++ )
    {
        CHairAsset* pHair = new CHairAsset();

        // numVerts
        sTokens.clear(); 
		sTokens.reserve(10);
        getline(inFile, sLine); // strand 0 numVerts 25 texcoord 0.000000 0.522833
        StringTokenizer(sLine, string(" "), sTokens, false);
        iter = sTokens.begin() + 3;
        sToken = *(iter);
        int numVerts = atoi(sToken.c_str());

		// Limit the maximum number of vertices per strand.
		if ( numVerts > maxNumOfVerticesInStrand )
			numVerts = maxNumOfVerticesInStrand;

        pHair->GetVertexArray().reserve(numVerts);

        int indexVert = 0;

        for ( int vertex = 0; vertex < numVerts; vertex++ )
        {
            getline(inFile, sLine);
            sTokens.clear(); 
			sTokens.reserve(10);
            int numFound = StringTokenizer(sLine, string(" "), sTokens, false);

            if ( numFound == 0 )
                continue;

            iter = sTokens.begin();

            if ( (*iter) == "-1.#INF" )
                continue;

            CVector3D pnt;
            
            // x
            sToken = (*iter);			
            pnt.m_X = (float)atof(sToken.c_str());

            // y
            ++iter;
            sToken = (*iter);			
            pnt.m_Y = (float)atof(sToken.c_str());

            // z
            ++iter;
            sToken = (*iter);			
            pnt.m_Z = (float)atof(sToken.c_str());
            
            CHairVertex vert;
            vert.m_Pos.Set(pnt.m_X, pnt.m_Y, pnt.m_Z);

            if ( bMovable )
            {
                if ( vertex == 0 || vertex == 1 )
                    vert.m_InvMass = 0;
                else
                    vert.m_InvMass = 1.0f;
            }
            else
            {
                if ( vertex == 0 || vertex == 1 || vertex == numVerts -1 || vertex == numVerts - 2 )
                    vert.m_InvMass = 0;
                else
                    vert.m_InvMass = 1.0f;
            }

            vert.m_GroupID = groupId;

            bool bPushback = true;

            if ( vertex > 0 )
            {
                const CHairVertex& vert_minus_1 = pHair->GetVertexArray()[indexVert-1];

                float length = (vert.m_Pos - vert_minus_1.m_Pos).Length();

                if ( length < 0.05f )
                    bPushback = false;
            }

            if ( bPushback )
            {
                pHair->GetVertexArray().push_back(vert);
                indexVert++;
            }
        }

		m_NumTotalVertices += (int)pHair->GetVertexArray().size();

        // add the new hair into m_Hairs
        if ( pHair->GetVertexArray().size() > 2 )
            m_Hairs.push_back(pHair);
        else
            delete pHair;
    }

    inFile.close();

    for ( int i = 0; i < (int)m_Hairs.size(); i++ )
    {
        m_Hairs[i]->ConstructAsset();
    }

    return true;	
}

void CHairAssetLoader::Clear()
{
    for ( int i = 0; i < (int)m_Hairs.size(); i++ )
    {
        if ( m_Hairs[i] )
            delete m_Hairs[i];
    }

    m_Hairs.clear();
}

