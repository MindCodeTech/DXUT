//--------------------------------------------------------------------------------------
// File: Geometry.cpp
//
// Classes for geometric primitives and collision and visibility testing
//
// Author: Gareth Thomas
//
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "..\\DXUT\\Core\\DXUT.h"
#include "Geometry.h"


AMD::BoundingBox AMD::TransformBounds( const BoundingBox& bounds, const D3DXMATRIX& transform )
{
	BoundingBox newBounds;
	newBounds.Reset();

	for ( int i = 0; i < 8; i++ ) 
	{
		D3DXVECTOR4 newPoint;
		D3DXVec4Transform( &newPoint, &bounds.GetPoint( i ), &transform );

		newBounds.AddPoint( newPoint );
	}
	
	return newBounds;
}

//--------------------------------------------------------------------------------------
// Helper function to normalize a plane
//--------------------------------------------------------------------------------------
void NormalizePlane( D3DXVECTOR4* pPlaneEquation )
{
    float mag;
    
    mag = sqrt( pPlaneEquation->x * pPlaneEquation->x + 
                pPlaneEquation->y * pPlaneEquation->y + 
                pPlaneEquation->z * pPlaneEquation->z );
    
    pPlaneEquation->x = pPlaneEquation->x / mag;
    pPlaneEquation->y = pPlaneEquation->y / mag;
    pPlaneEquation->z = pPlaneEquation->z / mag;
    pPlaneEquation->w = pPlaneEquation->w / mag;
}


//--------------------------------------------------------------------------------------
// Extract all 6 plane equations from frustum denoted by supplied matrix
//--------------------------------------------------------------------------------------
void ExtractPlanesFromFrustum( D3DXVECTOR4* pPlaneEquation, const D3DXMATRIX* pMatrix, bool bNormalize )
{
    // Left clipping plane
    pPlaneEquation[0].x = pMatrix->_14 + pMatrix->_11;
    pPlaneEquation[0].y = pMatrix->_24 + pMatrix->_21;
    pPlaneEquation[0].z = pMatrix->_34 + pMatrix->_31;
    pPlaneEquation[0].w = pMatrix->_44 + pMatrix->_41;
    
    // Right clipping plane
    pPlaneEquation[1].x = pMatrix->_14 - pMatrix->_11;
    pPlaneEquation[1].y = pMatrix->_24 - pMatrix->_21;
    pPlaneEquation[1].z = pMatrix->_34 - pMatrix->_31;
    pPlaneEquation[1].w = pMatrix->_44 - pMatrix->_41;
    
    // Top clipping plane
    pPlaneEquation[2].x = pMatrix->_14 - pMatrix->_12;
    pPlaneEquation[2].y = pMatrix->_24 - pMatrix->_22;
    pPlaneEquation[2].z = pMatrix->_34 - pMatrix->_32;
    pPlaneEquation[2].w = pMatrix->_44 - pMatrix->_42;
    
    // Bottom clipping plane
    pPlaneEquation[3].x = pMatrix->_14 + pMatrix->_12;
    pPlaneEquation[3].y = pMatrix->_24 + pMatrix->_22;
    pPlaneEquation[3].z = pMatrix->_34 + pMatrix->_32;
    pPlaneEquation[3].w = pMatrix->_44 + pMatrix->_42;
    
    // Near clipping plane
    pPlaneEquation[4].x = pMatrix->_13;
    pPlaneEquation[4].y = pMatrix->_23;
    pPlaneEquation[4].z = pMatrix->_33;
    pPlaneEquation[4].w = pMatrix->_43;
    
    // Far clipping plane
    pPlaneEquation[5].x = pMatrix->_14 - pMatrix->_13;
    pPlaneEquation[5].y = pMatrix->_24 - pMatrix->_23;
    pPlaneEquation[5].z = pMatrix->_34 - pMatrix->_33;
    pPlaneEquation[5].w = pMatrix->_44 - pMatrix->_43;
    
    // Normalize the plane equations, if requested
    if ( bNormalize )
    {
        NormalizePlane( &pPlaneEquation[0] );
        NormalizePlane( &pPlaneEquation[1] );
        NormalizePlane( &pPlaneEquation[2] );
        NormalizePlane( &pPlaneEquation[3] );
        NormalizePlane( &pPlaneEquation[4] );
        NormalizePlane( &pPlaneEquation[5] );
    }
}