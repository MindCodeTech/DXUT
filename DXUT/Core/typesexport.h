#pragma once

//using namespace std;

using namespace DirectX;

//template<class Type>
//typedef class DXUTAPI vector vector;
//typedef std std;
/*
namespace std
{

	template<class _Ty>
	class DXUTAPI mallocator
		: public _Allocator_base<_Ty>
	{	// generic allocator for objects of class _Ty
	public:
		typedef allocator mallocator;
	};

	template<class _Ty,
	class DXUTAPI _mAlloc0>
	struct _mVec_base_types
	{	// types needed for a container base
		typedef _mAlloc0 _mAlloc;
		//typedef _Alloc _mAlloc;
		typedef _mVec_base_types<_Ty, _mAlloc> _mMyt;
	};

	// TEMPLATE CLASS vector
	template<class _Ty,
	class DXUTAPI _mAlloc = allocator<_Ty> >
	class DXUTAPI mvector
	{	// varying size array of values
	public:
		typedef mvector<_Ty, _mAlloc> _mMyt;
		typedef vector mvector;
	};
}*/

namespace DirectX
{
	typedef struct DXUTAPI XMFLOAT2 XMFLOAT2;
	typedef struct DXUTAPI XMFLOAT3 XMFLOAT3;
	typedef struct DXUTAPI XMFLOAT4 XMFLOAT4;
	typedef struct DXUTAPI XMFLOAT4X4 XMFLOAT4X4;
}