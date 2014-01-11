//--------------------------------------------------------------------------------------
// File: PlatformHelpers.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#include "DXUTexp.h"

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DXUT

// Helper utility converts D3D API failures into exceptions.
inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw std::exception();
	}
}

// Helper sets a D3D resource name string (used by PIX and debug layer leak reporting).
inline void SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_z_ const char *name)
{
#if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
	resource->SetPrivateData( WKPDID_D3DDebugObjectName, static_cast<UINT>(strlen(name)), name );
#else
	UNREFERENCED_PARAMETER(resource);
	UNREFERENCED_PARAMETER(name);
#endif
}

// Helper sets a D3D resource name string (used by PIX and debug layer leak reporting).
template<UINT TNameLength>
inline void SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_z_ const char(&name)[TNameLength])
{
#if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#else
	UNREFERENCED_PARAMETER(resource);
	UNREFERENCED_PARAMETER(name);
#endif
}

    // Helper for output debug tracing
    inline void DebugTrace( _In_z_ _Printf_format_string_ const char* format, ... )
    {
#ifdef _DEBUG
        va_list args;
        va_start( args, format );

        char buff[1024];
        vsprintf_s( buff, format, args );
        OutputDebugStringA( buff );
#else
        UNREFERENCED_PARAMETER( format );
#endif
    }

// Helper smart-pointers
/*
	struct handle_closer { void operator()(HANDLE h) { if (h) CloseHandle(h); } };

	typedef public std::unique_ptr<void, handle_closer> ScopedHandle;

	inline HANDLE safe_handle( HANDLE h ) { return (h == INVALID_HANDLE_VALUE) ? 0 : h; }*/

//---------------------------------------------------------------------------------
struct DXUTAPI handle_closer { void operator()(HANDLE h) { assert(h != INVALID_HANDLE_VALUE); if (h) CloseHandle(h); } };

typedef public std::unique_ptr<void, handle_closer> ScopedHandle;

inline HANDLE safe_handle(HANDLE h) { return (h == INVALID_HANDLE_VALUE) ? 0 : h; }

//---------------------------------------------------------------------------------
struct DXUTAPI aligned_deleter { void operator()(void* p) { _aligned_free(p); } };

typedef std::unique_ptr<float, aligned_deleter> ScopedAlignedArrayFloat;

#ifdef USE_XNAMATH
typedef std::unique_ptr<XMVECTOR, aligned_deleter> ScopedAlignedArrayXMVECTOR;
#else
typedef std::unique_ptr<DirectX::XMVECTOR, aligned_deleter> ScopedAlignedArrayXMVECTOR;
#endif

//---------------------------------------------------------------------------------
#if defined(_MSC_VER) && (_MSC_VER >= 1610)

#include <wrl.h>

template<class T> class DXUTAPI ScopedObject : public Microsoft::WRL::ComPtr<T>
{
public:
	ScopedObject() : Microsoft::WRL::ComPtr<T>() {}
	ScopedObject(T *p) : Microsoft::WRL::ComPtr<T>(p) {}
	ScopedObject(const ScopedObject& other) : Microsoft::WRL::ComPtr(other) {}
};

#else

template<class T> class DXUTAPI ScopedObject
{
public:
	ScopedObject() : _pointer(nullptr) {}
	ScopedObject( T *p ) : _pointer(p) { if (_pointer) { _pointer->AddRef(); } }
	ScopedObject( const ScopedObject& other ) : _pointer(other._pointer) { if (_pointer) { _pointer->AddRef(); } }

	~ScopedObject()
	{
		if ( _pointer )
		{
			_pointer->Release();
			_pointer = nullptr;
		}
	}

	operator bool() const { return (_pointer != nullptr); }

	ScopedObject& operator= (_In_opt_ T* other)
	{
		if ( _pointer != other )
		{
			if ( _pointer) { _pointer->Release(); }
			_pointer = other;
			if ( other ) { other->AddRef(); };
		}
		return *this;
	}

	ScopedObject& operator= (const ScopedObject& other)
	{
		if ( _pointer != other._pointer )
		{
			if ( _pointer) { _pointer->Release(); }
			_pointer = other._pointer;
			if ( other._pointer ) { other._pointer->AddRef(); }
		}
		return *this;
	}

	T& operator*() { return *_pointer; }

	T* operator->() const { return _pointer; }

	T** operator&() { return &_pointer; }

	void Reset() { if ( _pointer ) { _pointer->Release(); _pointer = nullptr; } }

	T* Get() const { return _pointer; }
	T** GetAddressOf() { return &_pointer; }

	T** ReleaseAndGetAddressOf() { if ( _pointer ) { _pointer->Release(); _pointer = nullptr; } return &_pointer; }

	template<typename U>
	HRESULT As(_Inout_ U* p) { return _pointer->QueryInterface( _uuidof(U), reinterpret_cast<void**>( p ) ); }

	template<typename U>
	HRESULT As(_Out_ ScopedObject<U>* p ) { return _pointer->QueryInterface( _uuidof(U), reinterpret_cast<void**>( p->ReleaseAndGetAddressOf() ) ); }

private:
	T* _pointer;
};

#endif
NAMESPACE_DXUT_END

#if defined(_MSC_VER) && (_MSC_VER < 1610)

// Emulate the C++0x mutex and lock_guard types when building with Visual Studio versions < 2012.
namespace std
{
	class mutex
	{
	public:
		mutex()         { InitializeCriticalSection(&mCriticalSection); }
		~mutex()        { DeleteCriticalSection(&mCriticalSection); }

		void lock()     { EnterCriticalSection(&mCriticalSection); }
		void unlock()   { LeaveCriticalSection(&mCriticalSection); }
		bool try_lock() { return TryEnterCriticalSection(&mCriticalSection) != 0; }

	private:
		CRITICAL_SECTION mCriticalSection;

		mutex(mutex const&);
		mutex& operator= (mutex const&);
	};

	template<typename Mutex>
	class lock_guard
	{
	public:
		typedef Mutex mutex_type;

		explicit lock_guard(mutex_type& mutex)
			: mMutex(mutex)
		{
			mMutex.lock();
		}

		~lock_guard()
		{
			mMutex.unlock();
		}

	private:
		mutex_type& mMutex;

		lock_guard(lock_guard const&);
		lock_guard& operator= (lock_guard const&);
	};
}

#else   // _MSC_VER < 1610

#include <mutex>

#endif

#ifdef __cplusplus
EXTERN_C_END
#endif
