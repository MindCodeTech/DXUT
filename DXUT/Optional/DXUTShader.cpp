//--------------------------------------------------------------------------------------
// File: DXUTShader.cpp
//
// Shader compiling
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
#include "dxutstdafx.h"

using namespace DirectX;


#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

		namespace DXUT
		{

#if D3D_COMPILER_VERSION < 46

		namespace
		{
			class DXUTAPI CIncludeHandler : public ID3DInclude
				// Not as robust as D3D_COMPILE_STANDARD_FILE_INCLUDE, but it works in most cases
			{
			private:
				static const unsigned int MAX_INCLUDES = 9;

				struct sInclude
				{
					HANDLE         hFile;
					HANDLE         hFileMap;
					LARGE_INTEGER  FileSize;
					void           *pMapData;
				};

				struct sInclude     m_includeFiles[MAX_INCLUDES];
				size_t              m_nIncludes;
				bool                m_reset;
				WCHAR               m_workingPath[MAX_PATH];

			public:
				CIncludeHandler() : m_nIncludes(0), m_reset(false)
				{
					if ( !GetCurrentDirectoryW( MAX_PATH, m_workingPath ) )
						*m_workingPath = 0;

					for ( size_t i = 0; i < MAX_INCLUDES; ++i )
					{
						m_includeFiles[i].hFile = INVALID_HANDLE_VALUE;
						m_includeFiles[i].hFileMap = INVALID_HANDLE_VALUE;
						m_includeFiles[i].pMapData = nullptr;
					}
				}
				~CIncludeHandler()
				{
					for ( size_t i = 0; i < m_nIncludes; ++i )
					{
						UnmapViewOfFile( m_includeFiles[i].pMapData );

						if ( m_includeFiles[i].hFileMap != INVALID_HANDLE_VALUE)
							CloseHandle( m_includeFiles[i].hFileMap );

						if ( m_includeFiles[i].hFile != INVALID_HANDLE_VALUE)
							CloseHandle( m_includeFiles[i].hFile );
					}

					m_nIncludes = 0;

					if ( m_reset && *m_workingPath )
					{
						SetCurrentDirectoryW( m_workingPath );
					}
				}

				STDMETHOD(Open( D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes ) )
				{
					UNREFERENCED_PARAMETER(IncludeType);
					UNREFERENCED_PARAMETER(pParentData);

					size_t incIndex = m_nIncludes+1;

					// Make sure we have enough room for this include file
					if ( incIndex >= MAX_INCLUDES )
						return E_FAIL;

					// try to open the file
					m_includeFiles[incIndex].hFile  = CreateFileA( pFileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr );
					if( INVALID_HANDLE_VALUE == m_includeFiles[incIndex].hFile )
					{
						return E_FAIL;
					}

					// Get the file size
					GetFileSizeEx( m_includeFiles[incIndex].hFile, &m_includeFiles[incIndex].FileSize );

					// Use Memory Mapped File I/O for the header data
					m_includeFiles[incIndex].hFileMap = CreateFileMappingA( m_includeFiles[incIndex].hFile, nullptr, PAGE_READONLY, m_includeFiles[incIndex].FileSize.HighPart, m_includeFiles[incIndex].FileSize.LowPart, pFileName);
					if( !m_includeFiles[incIndex].hFileMap )
					{
						if (m_includeFiles[incIndex].hFile != INVALID_HANDLE_VALUE)
							CloseHandle( m_includeFiles[incIndex].hFile );
						return E_FAIL;
					}

					// Create Map view
					*ppData = MapViewOfFile( m_includeFiles[incIndex].hFileMap, FILE_MAP_READ, 0, 0, 0 );
					*pBytes = m_includeFiles[incIndex].FileSize.LowPart;

					// Success - Increment the include file count
					m_nIncludes = incIndex;

					return S_OK;
				}

				STDMETHOD(Close( LPCVOID pData ))
				{
					UNREFERENCED_PARAMETER(pData);
					// Defer Closure until the container destructor
					return S_OK;
				}

				void SetCWD( LPCWSTR pFileName )
				{
					WCHAR filePath[MAX_PATH];
					wcscpy_s( filePath, MAX_PATH, pFileName );

					WCHAR *strLastSlash = wcsrchr( filePath, L'\\' );
					if( strLastSlash )
					{
						// Chop the exe name from the exe path
						*strLastSlash = 0;
						m_reset = true;
						SetCurrentDirectoryW( filePath );
					}
				}
			};
		}; // namespace

#endif

		DXUTAPI HRESULT WINAPI CompileShaderFromFile( LPCWSTR szFileName,
			const D3D_SHADER_MACRO* pDefines,
			LPCSTR szEntryPoint, LPCSTR szShaderModel,
			UINT Flags1, UINT Flags2,
			ID3DBlob** ppBlobOut )
		{
			HRESULT hr = S_OK;

			// find the file
			WCHAR str[MAX_PATH];
			V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, szFileName ) );

			//DWORD Flags1 = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
			// Setting this flag improves the shader debugging experience, but still allows
			// the shaders to be optimized and to run exactly the way they will run in
			// the release configuration of this program.
			Flags1 |= D3DCOMPILE_DEBUG;
#endif

			ID3DBlob* pErrorBlob = nullptr;

#if D3D_COMPILER_VERSION >= 46

			hr = D3DCompileFromFile( str, pDefines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				szEntryPoint, szShaderModel, Flags1, Flags2,
				ppBlobOut, &pErrorBlob );
#else

			ScopedHandle hFile( safe_handle( CreateFileW( str, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr ) ) );

			if ( !hFile )
				return HRESULT_FROM_WIN32( GetLastError() );

			LARGE_INTEGER FileSize = { 0 };

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
			FILE_STANDARD_INFO fileInfo;
			if ( !GetFileInformationByHandleEx( hFile.get(), FileStandardInfo, &fileInfo, sizeof(fileInfo) ) )
			{
				return HRESULT_FROM_WIN32( GetLastError() );
			}
			FileSize = fileInfo.EndOfFile;
#else
			GetFileSizeEx( hFile.get(), &FileSize );
#endif

			if (!FileSize.LowPart || FileSize.HighPart > 0)
				return E_FAIL;

			std::unique_ptr<char[]> fxData;
			fxData.reset( new (std::nothrow) char[ FileSize.LowPart ] );
			if ( !fxData )
				return E_OUTOFMEMORY;

			DWORD BytesRead = 0;
			if ( !ReadFile( hFile.get(), fxData.get(), FileSize.LowPart, &BytesRead, nullptr ) )
				return HRESULT_FROM_WIN32( GetLastError() );

			if (BytesRead < FileSize.LowPart)
				return E_FAIL;

			char pSrcName[MAX_PATH];
			int result = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, str, -1, pSrcName, MAX_PATH, nullptr, FALSE );
			if ( !result )
				return E_FAIL;

			const CHAR* pstrName = strrchr( pSrcName, '\\' );
			if (!pstrName)
			{
				pstrName = pSrcName;
			}
			else
			{
				pstrName++;
			}

			std::unique_ptr<CIncludeHandler> includes( new (std::nothrow) CIncludeHandler );
			if ( !includes )
				return E_OUTOFMEMORY;

			includes->SetCWD( str );

			hr = D3DCompile( fxData.get(), BytesRead, pstrName, pDefines, includes.get(),
				pEntrypoint, pTarget, Flags1, Flags2,
				ppCode, &pErrorBlob );

#endif
			if( FAILED(hr) )
			{
#pragma warning( suppress : 6102 )
				if( pErrorBlob != nullptr )
					OutputDebugStringA( reinterpret_cast<const char*>( pErrorBlob->GetBufferPointer() ) );
				SAFE_RELEASE( pErrorBlob );
				return hr;
			}
			SAFE_RELEASE( pErrorBlob );

			return S_OK;
		}

			}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
	}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
	}
#endif