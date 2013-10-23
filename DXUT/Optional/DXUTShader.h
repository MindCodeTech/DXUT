
#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

		namespace DXUT
		{

//--------------------------------------------------------------------------------------
// Find and compile the specified shader
//--------------------------------------------------------------------------------------
DXUTAPI HRESULT WINAPI CompileShaderFromFile( _In_z_ LPCWSTR szFileName,
							  _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) const D3D_SHADER_MACRO* pDefines,
							  _In_z_ LPCSTR szEntryPoint, _In_z_ LPCSTR szShaderModel,
							  _In_ UINT Flags1, _In_ UINT Flags2, 
							  _Outptr_ ID3DBlob** ppBlobOut );

		}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
