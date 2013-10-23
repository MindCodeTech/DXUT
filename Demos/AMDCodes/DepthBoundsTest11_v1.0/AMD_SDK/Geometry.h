//--------------------------------------------------------------------------------------
// File: Geometry.h
//
// Classes for geometric primitives and collision and visibility testing
//
// Author: Gareth Thomas
//
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef __AMD_GEOMETRY_H__
#define __AMD_GEOMETRY_H__



namespace AMD
{

class BoundingBox
{
public:

	BoundingBox() {}
	BoundingBox( const D3DXVECTOR4& min, const D3DXVECTOR4& max ) : m_min( min ), m_max( max ) {}
	BoundingBox( const D3DXVECTOR3& min, const D3DXVECTOR3& max ) : m_min( D3DXVECTOR4( min, 1.0f ) ), m_max( D3DXVECTOR4( max, 1.0f ) ) {}
	~BoundingBox() {}

	void Reset() { m_min = D3DXVECTOR4( FLT_MAX, FLT_MAX, FLT_MAX, 1.0f ); m_max = D3DXVECTOR4( -FLT_MAX, -FLT_MAX, -FLT_MAX, 1.0f ); }
	
	const D3DXVECTOR4& GetMin() const { return m_min; }
	const D3DXVECTOR4& GetMax() const { return m_max; }
	D3DXVECTOR4 GetDimensions() const { return m_max - m_min; }

	D3DXVECTOR4 GetPoint( int i ) const { return D3DXVECTOR4( i & 0x1 ? m_max.x : m_min.x, i & 0x2 ? m_max.y : m_min.y, i & 0x4 ? m_max.z : m_min.z, 1.0f ); }

	void AddPoint( const D3DXVECTOR3& p ) { AddPoint( D3DXVECTOR4( p, 1.0f ) ); }
	void AddPoint( const D3DXVECTOR4& p ) { m_min.x = min( m_min.x, p.x ); m_min.y = min( m_min.y, p.y ); m_min.z = min( m_min.z, p.z ); m_max.x = max( m_max.x, p.x ); m_max.y = max( m_max.y, p.y ); m_max.z = max( m_max.z, p.z ); }

private:

	D3DXVECTOR4		m_min;
	D3DXVECTOR4		m_max;
};


BoundingBox TransformBounds( const BoundingBox& bounds, const D3DXMATRIX& transform );

void ExtractPlanesFromFrustum( D3DXVECTOR4* pPlaneEquation, const D3DXMATRIX* pMatrix, bool bNormalize );


}

#endif

