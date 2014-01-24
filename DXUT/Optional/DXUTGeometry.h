//--------------------------------------------------------------------------------------
// File: DXUTGeometry.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=320437
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#include "DXUT.h"
#include "DXUTMathHelper.h"

namespace_DXUT

struct DXUTAPI Vertex
{
    Vertex(){}
    Vertex(const XMFLOAT3& p, const XMFLOAT3& n, const XMFLOAT3& t, const XMFLOAT2& uv)
        : Position(p), Normal(n), TangentU(t), TexC(uv){}
    Vertex(
        float px, float py, float pz, 
        float nx, float ny, float nz,
        float tx, float ty, float tz,
        float u, float v)
        : Position(px,py,pz), Normal(nx,ny,nz),
        TangentU(tx, ty, tz), TexC(u,v){}

    XMFLOAT3 Position;
    XMFLOAT3 Normal;
    XMFLOAT3 TangentU;
    XMFLOAT2 TexC;
};

struct DXUTAPI GeneratedMesh
{
    std::vector<Vertex *> Vertices;
    std::vector<UINT> Indices;
};

struct DXUTAPI FaceType
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
};

class DXUTAPI GeometryGenerator
{
public:
	///<summary>
	/// Creates a box centered at the origin with the given dimensions.
	///</summary>
	void CreateBox(float width, float height, float depth, GeneratedMesh& meshData);

	///<summary>
	/// Creates a sphere centered at the origin with the given radius.  The
	/// slices and stacks parameters control the degree of tessellation.
	///</summary>
	void CreateSphere(float radius, UINT sliceCount, UINT stackCount, GeneratedMesh& meshData);

	///<summary>
	/// Creates a geosphere centered at the origin with the given radius.  The
	/// depth controls the level of tessellation.
	///</summary>
	void CreateGeosphere(float radius, UINT numSubdivisions, GeneratedMesh& meshData);

	///<summary>
	/// Creates a cylinder parallel to the y-axis, and centered about the origin.  
	/// The bottom and top radius can vary to form various cone shapes rather than true
	// cylinders.  The slices and stacks parameters control the degree of tessellation.
	///</summary>
	void CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, GeneratedMesh& meshData);

	///<summary>
	/// Creates an mxn grid in the xz-plane with m rows and n columns, centered
	/// at the origin with the specified width and depth.
	///</summary>
	void CreateGrid(float width, float depth, UINT m, UINT n, GeneratedMesh& meshData);

	///<summary>
	/// Creates a quad covering the screen in NDC coordinates.  This is useful for
	/// postprocessing effects.
	///</summary>
	void CreateFullscreenQuad(GeneratedMesh& meshData);

private:
	void Subdivide(GeneratedMesh& meshData);
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, GeneratedMesh& meshData);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, GeneratedMesh& meshData);
};

namespace_DXUT_end

