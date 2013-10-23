//--------------------------------------------------------------------------------------
// File: ShaderCache.cpp
//
// Class implementation for the ShaderCache interface. Allows the user to add shaders to a list
// which is then compiled in parallel to object files. Future calls to create the shaders,
// will simply re-use the object files, making craetion time very fast. The option is there,
// to force the regeneration of object files.
//
// Assumption, relies on following directory structure:
//
// SolutionDir\Shaders\fxc.exe
// SolutionDir\Shaders\Source\
// SolutionDir\Shaders\Obj\
// SolutionDir\Shaders\Errors\
//
// Author: Jon Story
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#include "..\\DXUT\\Core\\DXUT.h"
#include "..\\DXUT\\Optional\\SDKmisc.h"
#include "ShaderCache.h"
#include "Process.h"


using namespace AMD;


// The done event handle 
static HANDLE   s_hDoneEvent = 0;


//--------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------
ShaderCache::Shader::Shader()
{
    m_eShaderType = SHADER_TYPE_UNKNOWN;
    m_ppShader = NULL;
    m_ppInputLayout = NULL;
    m_pInputLayoutDesc = NULL;
    m_uNumDescElements = 0;
    
    memset( m_wsTarget, '\0', sizeof( wchar_t[m_uTARGET_MAX_LENGTH] ) );
    memset( m_wsEntryPoint, '\0', sizeof( wchar_t[m_uENTRY_POINT_MAX_LENGTH] ) );
    memset( m_wsSourceFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );

    m_uNumMacros = 0;
    m_pMacros = NULL;
    
    memset( m_wsObjectFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );
    memset( m_wsErrorFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );
    memset( m_wsAssemblyFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );
    memset( m_wsPreprocessFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );
    memset( m_wsHashFile, '\0', sizeof( wchar_t[m_uFILENAME_MAX_LENGTH] ) );
    memset( m_wsCommandLine, '\0', sizeof( wchar_t[m_uCOMMAND_LINE_MAX_LENGTH] ) );
    memset( m_wsPreprocessCommandLine, '\0', sizeof( wchar_t[m_uCOMMAND_LINE_MAX_LENGTH] ) );

    m_bBeingProcessed = false;

    m_pHash = NULL;
    m_uHashLength = 0;

}


//--------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------
ShaderCache::Shader::~Shader()
{
    if( NULL != m_pMacros )
    {
        delete[] m_pMacros;
        m_pMacros = NULL;
    }

    if( NULL != m_pHash )
    {
        delete[] m_pHash;
        m_pHash = NULL;
    }

    for( int iElement = 0; iElement < (int)m_uNumDescElements; iElement++ )
    {
        delete[] m_pInputLayoutDesc[iElement].SemanticName;
    }
    delete m_pInputLayoutDesc;
    m_pInputLayoutDesc = NULL;
}


//--------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------
ShaderCache::ShaderCache()
{
    m_ShaderList.clear();
    m_PreprocessList.clear();
    m_CompileList.clear();
    m_CreateList.clear();
	m_ShaderList.empty();
    m_PreprocessList.empty();
    m_CompileList.empty();
    m_CreateList.empty();

	BOOL bRet;

	GetCurrentDirectoryW( m_uPATHNAME_MAX_LENGTH, m_wsWorkingDir );
    	
    wchar_t wsShadersDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsShadersDir, L"%s%s", m_wsWorkingDir, L"\\Shaders" );
    bRet = CreateDirectoryW( wsShadersDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsCacheDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsCacheDir, L"%s%s", wsShadersDir, L"\\Cache" );
    bRet = CreateDirectoryW( wsCacheDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsObjectDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsObjectDir, L"%s%s", wsCacheDir, L"\\Object" );
    bRet = CreateDirectoryW( wsObjectDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsObjectDebugDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsObjectDebugDir, L"%s%s", wsCacheDir, L"\\Object\\Debug" );
    bRet = CreateDirectoryW( wsObjectDebugDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsObjectReleaseDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsObjectReleaseDir, L"%s%s", wsCacheDir, L"\\Object\\Release" );
    bRet = CreateDirectoryW( wsObjectReleaseDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsErrorDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsErrorDir, L"%s%s", wsCacheDir, L"\\Error" );
    bRet = CreateDirectoryW( wsErrorDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsAssemblyDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsAssemblyDir, L"%s%s", wsCacheDir, L"\\Assembly" );
    bRet = CreateDirectoryW( wsAssemblyDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsPreprocessDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsPreprocessDir, L"%s%s", wsCacheDir, L"\\Preprocess" );
    bRet = CreateDirectoryW( wsPreprocessDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsHashDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsHashDir, L"%s%s", wsCacheDir, L"\\Hash" );
    bRet = CreateDirectoryW( wsHashDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsHashDebugDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsHashDebugDir, L"%s%s", wsCacheDir, L"\\Hash\\Debug" );
    bRet = CreateDirectoryW( wsHashDebugDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    wchar_t wsHashReleaseDir[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsHashReleaseDir, L"%s%s", wsCacheDir, L"\\Hash\\Release" );
    bRet = CreateDirectoryW( wsHashReleaseDir, NULL );
    if( bRet == ERROR_PATH_NOT_FOUND )
	{
        assert( false );
    }

    SYSTEM_INFO sysinfo; 
    GetSystemInfo( &sysinfo );  
    m_uNumCPUCores = ( sysinfo.dwNumberOfProcessors > 1 ) ? ( sysinfo.dwNumberOfProcessors - 1 ) : ( 1 );

    s_hDoneEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	SetEvent( s_hDoneEvent );
        
    m_CreateType = CREATE_TYPE_USE_CACHED;

    m_bShadersCreated = false;
	m_bAbort = false;
    m_bPrintedProgress = false;

    m_ppProgressStrings = NULL;
    m_uProgressCounter = 0;

	m_bForceDebugShaders = false;

    if( !CheckFXC() )
    {
        // fxc.exe is assumed to be in SolutionDir\Shaders
        _asm int 3;
    }
}


//--------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------
ShaderCache::~ShaderCache()
{
	WaitForSingleObject( s_hDoneEvent, INFINITE );
    CloseHandle( s_hDoneEvent );

    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
        delete pShader;
    }
    
    m_ShaderList.empty();
    m_PreprocessList.empty();
    m_CompileList.empty();
    m_CreateList.empty();

    if( NULL != m_ppProgressStrings )
    {
        delete[] m_ppProgressStrings;
        m_ppProgressStrings = NULL;
    }
}


//--------------------------------------------------------------------------------------
// DXUT framework hook method (flags shaders as needing creation)
//--------------------------------------------------------------------------------------
void ShaderCache::OnDestroyDevice()
{
	m_bShadersCreated = false;
}


//--------------------------------------------------------------------------------------
// Called by app when WM_QUIT is posted, so that shader generation can be aborted
//--------------------------------------------------------------------------------------
void ShaderCache::Abort()
{
	m_bAbort = true;
}


//--------------------------------------------------------------------------------------
// User adds a shader to the cache
//--------------------------------------------------------------------------------------
bool ShaderCache::AddShader(    ID3D11DeviceChild** ppShader, 
                                SHADER_TYPE ShaderType, 
                                const wchar_t* pwsTarget, 
                                const wchar_t* pwsEntryPoint, 
                                const wchar_t* pwsSourceFile,
                                unsigned int uNumMacros, 
                                Macro* pMacros,
                                ID3D11InputLayout** ppInputLayout,
                                const D3D11_INPUT_ELEMENT_DESC* pInputLayoutDesc,
                                unsigned int uNumDescElements )
{
    assert( NULL != ppShader );
    assert( ( ShaderType >= SHADER_TYPE_VERTEX ) && ( ShaderType <= SHADER_TYPE_COMPUTE ) );
    assert( ( NULL != pwsTarget ) && ( wcslen( pwsTarget ) <= m_uTARGET_MAX_LENGTH ) );
    assert( ( NULL != pwsEntryPoint) && ( wcslen( pwsEntryPoint ) <= m_uENTRY_POINT_MAX_LENGTH ) );
    assert( ( NULL != pwsSourceFile ) && ( wcslen( pwsSourceFile ) <= m_uFILENAME_MAX_LENGTH ) );
    if( uNumMacros > 0 )
    {
        assert( NULL != pMacros );
    }

    Shader* pShader = new Shader();
    pShader->m_ppShader = ppShader;
    pShader->m_eShaderType = ShaderType;

    if( pShader->m_eShaderType == SHADER_TYPE_VERTEX )
    {
        pShader->m_uNumDescElements = uNumDescElements;

        if( pShader->m_uNumDescElements > 0 )
        {
            assert( NULL != ppInputLayout );
            assert( NULL != pInputLayoutDesc );

            pShader->m_ppInputLayout = ppInputLayout;
            
            pShader->m_pInputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[pShader->m_uNumDescElements];
            
            memcpy( pShader->m_pInputLayoutDesc, pInputLayoutDesc, sizeof( D3D11_INPUT_ELEMENT_DESC ) * pShader->m_uNumDescElements );

            for( int iElement = 0; iElement < (int)pShader->m_uNumDescElements; iElement++ )
            {
                pShader->m_pInputLayoutDesc[iElement].SemanticName = new char[m_uFILENAME_MAX_LENGTH];
                strcpy_s( (char*)pShader->m_pInputLayoutDesc[iElement].SemanticName, m_uFILENAME_MAX_LENGTH, (char*)pInputLayoutDesc[iElement].SemanticName ); 
            }
        }
    }
   
    wcscpy_s( pShader->m_wsTarget, m_uTARGET_MAX_LENGTH, pwsTarget );
    wcscpy_s( pShader->m_wsEntryPoint, m_uENTRY_POINT_MAX_LENGTH, pwsEntryPoint );
    wcscpy_s( pShader->m_wsSourceFile, m_uFILENAME_MAX_LENGTH, pwsSourceFile );

    pShader->m_uNumMacros = uNumMacros;
    if( pShader->m_uNumMacros > 0 )
    {
        pShader->m_pMacros = new Macro[pShader->m_uNumMacros];
        memcpy( pShader->m_pMacros, pMacros, sizeof( Macro ) * pShader->m_uNumMacros );
    }

    // Object, error, assembly, preprocess, and hash file names
    wchar_t wsFileNameBody[m_uFILENAME_MAX_LENGTH];
    #ifdef _DEBUG
        wcscat_s( pShader->m_wsObjectFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Object\\Debug\\" );
        wcscat_s( pShader->m_wsHashFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Hash\\Debug\\" );
    #else
        wcscat_s( pShader->m_wsObjectFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Object\\Release\\" );
        wcscat_s( pShader->m_wsHashFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Hash\\Release\\" );
    #endif
    wcscat_s( pShader->m_wsErrorFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Error\\" );
    wcscat_s( pShader->m_wsAssemblyFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Assembly\\" );
    wcscat_s( pShader->m_wsPreprocessFile, m_uFILENAME_MAX_LENGTH, L"Shaders\\Cache\\Preprocess\\" );
    wcscpy_s( wsFileNameBody, m_uFILENAME_MAX_LENGTH, pwsEntryPoint ); 
    for( int iMacro = 0; iMacro < (int)pShader->m_uNumMacros; ++iMacro )
    {
        wchar_t wsValue[64];
        wcscat_s( wsFileNameBody, m_uFILENAME_MAX_LENGTH, L"_" );
        wcscat_s( wsFileNameBody, m_uFILENAME_MAX_LENGTH, pShader->m_pMacros[iMacro].m_wsName );
        wcscat_s( wsFileNameBody, m_uFILENAME_MAX_LENGTH, L"=" );
        _itow_s( pShader->m_pMacros[iMacro].m_iValue, wsValue, 10 );
        wcscat_s( wsFileNameBody, m_uFILENAME_MAX_LENGTH, wsValue );
    }
    wcscat_s( pShader->m_wsObjectFile, m_uFILENAME_MAX_LENGTH, wsFileNameBody );
    wcscat_s( pShader->m_wsErrorFile, m_uFILENAME_MAX_LENGTH, wsFileNameBody );
    wcscat_s( pShader->m_wsAssemblyFile, m_uFILENAME_MAX_LENGTH, wsFileNameBody );
    wcscat_s( pShader->m_wsPreprocessFile, m_uFILENAME_MAX_LENGTH, wsFileNameBody );
    wcscat_s( pShader->m_wsHashFile, m_uFILENAME_MAX_LENGTH, wsFileNameBody );
    wcscat_s( pShader->m_wsObjectFile, m_uFILENAME_MAX_LENGTH, L".obj" );
    wcscat_s( pShader->m_wsErrorFile, m_uFILENAME_MAX_LENGTH, L".txt" );
    wcscat_s( pShader->m_wsAssemblyFile, m_uFILENAME_MAX_LENGTH, L".asm" );
    wcscat_s( pShader->m_wsPreprocessFile, m_uFILENAME_MAX_LENGTH, L".ppf" );
    wcscat_s( pShader->m_wsHashFile, m_uFILENAME_MAX_LENGTH, L".hsh" );
    
    // Compilation flags based on build profile
    wchar_t wsCompilationFlags[m_uFILENAME_MAX_LENGTH];
    #ifdef _DEBUG
        // Best flags for shader debugging
        // /Zi - Enable debugging information
        // /Od - Disable optimizations
        // /Gfp - Prefer flow control constructs
        wcscpy_s( wsCompilationFlags, m_uFILENAME_MAX_LENGTH, L" /Zi /Od /Gfp" ); 
    #else
		if( m_bForceDebugShaders )
		{
			// Best flags for shader debugging
			// /Zi - Enable debugging information
			// /Od - Disable optimizations
			// /Gfp - Prefer flow control constructs
			wcscpy_s( wsCompilationFlags, m_uFILENAME_MAX_LENGTH, L" /Od" );
		}
		else
		{
			// Select optimization level ( 1 is default)
			// /O{0,1,2,3} - Optimization Level
			wcscpy_s( wsCompilationFlags, m_uFILENAME_MAX_LENGTH, L" /O1" );
		}
    #endif

    // Command line
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /T " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pwsTarget );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, wsCompilationFlags );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /E " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pwsEntryPoint );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsSourceFile );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /Fo " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsObjectFile );
    for( int iMacro = 0; iMacro < (int)pShader->m_uNumMacros; ++iMacro )
    {
        wchar_t wsValue[64];
        wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /D " );
        wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_pMacros[iMacro].m_wsName );
        wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L"=" );
        _itow_s( pShader->m_pMacros[iMacro].m_iValue, wsValue, 10 );
        wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, wsValue );
    }
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /Fe " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsErrorFile );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /Fc " );
    wcscat_s( pShader->m_wsCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsAssemblyFile );

    // Preprocess command line
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /E " );
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pwsEntryPoint );
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" " );
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsSourceFile );
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /P " );
    wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_wsPreprocessFile );
    for( int iMacro = 0; iMacro < (int)pShader->m_uNumMacros; ++iMacro )
    {
        wchar_t wsValue[64];
        wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L" /D " );
        wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, pShader->m_pMacros[iMacro].m_wsName );
        wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, L"=" );
        _itow_s( pShader->m_pMacros[iMacro].m_iValue, wsValue, 10 );
        wcscat_s( pShader->m_wsPreprocessCommandLine, m_uCOMMAND_LINE_MAX_LENGTH, wsValue );
    }
    
    m_ShaderList.push_back( pShader );

    return true;
}


//--------------------------------------------------------------------------------------
// The shader thread proc, has to be public, but must not be called by user
//--------------------------------------------------------------------------------------
DWORD WINAPI _GenerateShadersThreadProc( void* pParameter )
{
    ShaderCache* pShaderCache = (ShaderCache*)pParameter;
	
    pShaderCache->GenerateShadersThreadProc();

    SetEvent( s_hDoneEvent ); 

    return 0;
}


//--------------------------------------------------------------------------------------
// Initiates shader generation based upon the creation flags:
// CREATE_TYPE_FORCE_COMPILE,      // Clean the cache, and compile all
// CREATE_TYPE_COMPILE_CHANGES,    // Only compile shaders that have changed (development mode)
// CREATE_TYPE_USE_CACHED,         // Use cached shaders (release mode)
//--------------------------------------------------------------------------------------
HRESULT ShaderCache::GenerateShaders( CREATE_TYPE CreateType )
{
	DWORD dwRet = WaitForSingleObject( s_hDoneEvent, 0 );

    if( dwRet == WAIT_OBJECT_0 )
    {
		m_CreateType = CreateType;
		m_bShadersCreated = false;
		m_bPrintedProgress = false;

		for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++ )
		{
			Shader* pShader = *it;

			if( ( m_CreateType == CREATE_TYPE_COMPILE_CHANGES ) ||
				( m_CreateType == CREATE_TYPE_FORCE_COMPILE ) || 
				( !CheckObjectFile( pShader ) ) )
			{
				m_PreprocessList.push_back( pShader );
			}
			else
			{
				m_CreateList.push_back( pShader );
			}
		}

		if( m_PreprocessList.size() )
		{
			m_ppProgressStrings = new wchar_t*[m_PreprocessList.size() * 2];
			m_uProgressCounter = 0;

			ResetEvent( s_hDoneEvent );
			QueueUserWorkItem( _GenerateShadersThreadProc, this, WT_EXECUTELONGFUNCTION );
		}
		else
		{
			SetEvent( s_hDoneEvent );
		}
	}
   
    return S_OK;
}


//--------------------------------------------------------------------------------------
//  Called by the thread proc to actaully do the work
//--------------------------------------------------------------------------------------
void ShaderCache::GenerateShadersThreadProc()
{
    DeleteErrorFiles();
    DeleteAssemblyFiles();
    DeletePreprocessFiles();

    if( m_CreateType == CREATE_TYPE_FORCE_COMPILE )
    {
        DeleteHashFiles();
        DeleteObjectFiles();
    }

    PreprocessShaders();
    CompileShaders();
}


//--------------------------------------------------------------------------------------
// Renders the progress of the shader generation process
//--------------------------------------------------------------------------------------
void ShaderCache::RenderProgress( CDXUTTextHelper* g_pTxtHelper, int iFontHeight, D3DXCOLOR FontColor )
{
    wchar_t wsOverallProgress[m_uPATHNAME_MAX_LENGTH];

    g_pTxtHelper->Begin();
    g_pTxtHelper->SetForegroundColor( FontColor );
    g_pTxtHelper->SetInsertionPos( 5, 5 );

    int iNumLines = (int)( ( DXUTGetDXGIBackBufferSurfaceDesc()->Height - ( iFontHeight ) ) * 0.99f / iFontHeight );
    
    if( !m_bPrintedProgress && !m_PreprocessList.size() )
    {
        swprintf_s( wsOverallProgress, L"*** Shader Cache: Creating Shaders... ***" );
        g_pTxtHelper->DrawTextLine( wsOverallProgress );

        m_bPrintedProgress = true;
    }
    else
    {
        swprintf_s( wsOverallProgress, L"*** Shader Cache: Shaders to Preprocess = %d, Compile = %d ***", m_PreprocessList.size(), m_CompileList.size() );
        g_pTxtHelper->DrawTextLine( wsOverallProgress );
    }

    if( NULL != m_ppProgressStrings )
    {
        g_pTxtHelper->SetInsertionPos( 5, 5 + iFontHeight );
        
        int iCounter = m_uProgressCounter;
        int iStrings = ( iCounter < iNumLines ) ? ( iCounter ) : ( iNumLines ); 

        for( int i = iCounter - iStrings; i < iCounter; i++ )
        {
            g_pTxtHelper->DrawTextLine( m_ppProgressStrings[i] );
        }
    }
    
	g_pTxtHelper->End();
}


//--------------------------------------------------------------------------------------
// boolean method to determine if the shaders are ready
//--------------------------------------------------------------------------------------
bool ShaderCache::ShadersReady()
{
    DWORD dwRet = WaitForSingleObject( s_hDoneEvent, 0 );

    if( dwRet == WAIT_OBJECT_0 )
    {
        if( m_bPrintedProgress )
        {
            if( !m_bShadersCreated )
            {
                CreateShaders();
                m_bShadersCreated = true;

                if( NULL != m_ppProgressStrings )
                {
                    delete[] m_ppProgressStrings;
                    m_ppProgressStrings = NULL;
                    m_uProgressCounter = 0;
                }
            }

            return true;
        }
    }
  
    return false;
}


//--------------------------------------------------------------------------------------
// Private methods:
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Preprocesses shaders in the list, and generates a hash file, this is subsequently used to
// determine if a shader has changed
//--------------------------------------------------------------------------------------
void ShaderCache::PreprocessShaders()
{
    Shader* pShader = NULL;
    unsigned int uNumWorkThreads = 0;

    while( m_PreprocessList.size() )
    {
        bool bRemove = false;

        for( std::list<Shader*>::iterator it = m_PreprocessList.begin(); it != m_PreprocessList.end(); it++ )
        {
            if( bRemove )
            {
                m_PreprocessList.remove( pShader );

                bRemove = false; 
            }

            pShader = *it;

            if( uNumWorkThreads < m_uNumCPUCores )
            {
                if( pShader->m_bBeingProcessed == false )
                {
                    PreprocessShader( pShader );

                    pShader->m_bBeingProcessed = true;

                    uNumWorkThreads++;
                }
            }

            if( CreateHashFromPreprocessFile( pShader ) )
            {
                m_ppProgressStrings[m_uProgressCounter++] = pShader->m_wsPreprocessFile;

                if( !CompareHash( pShader ) )
                {
                    DeleteObjectFile( pShader );
                    
                    WriteHashFile( pShader );

                    m_CompileList.push_back( pShader );
                }
                else
                {
                    if( CheckObjectFile( pShader ) )
                    {
                        m_CreateList.push_back( pShader );
                    }
                    else
                    {
                        m_CompileList.push_back( pShader );
                    }
                }

                pShader->m_bBeingProcessed = false;

				if ( uNumWorkThreads > 0 )
					uNumWorkThreads--;

                bRemove = true;
            }
        }

        if( bRemove )
        {
            m_PreprocessList.remove( pShader );
        }

		if( m_bAbort )
		{
			break;
		}
    }
}


//--------------------------------------------------------------------------------------
// Compiles the shaders in the list
//--------------------------------------------------------------------------------------
void ShaderCache::CompileShaders()
{
    Shader* pShader = NULL;
    unsigned int uNumWorkThreads = 0;

    while( m_CompileList.size() )
    {
        bool bRemove = false;

        for( std::list<Shader*>::iterator it = m_CompileList.begin(); it != m_CompileList.end(); it++ )
        {
            if( bRemove )
            {
                m_CompileList.remove( pShader );

                bRemove = false;
            }

            pShader = *it;

            if( uNumWorkThreads < m_uNumCPUCores )
            {
                if( pShader->m_bBeingProcessed == false )
                {
                    CompileShader( pShader );
                    
                    pShader->m_bBeingProcessed = true;

                    uNumWorkThreads++;
                }
            }

            if( CheckObjectFile( pShader ) )
            {
                m_ppProgressStrings[m_uProgressCounter++] = pShader->m_wsObjectFile;

                m_CreateList.push_back( pShader );

                pShader->m_bBeingProcessed = false;

				if ( uNumWorkThreads > 0 )
					uNumWorkThreads--;

                bRemove = true;
            }

            CheckErrorFile( pShader );
        }

        if( bRemove )
        {
            m_CompileList.remove( pShader );
        }

		if( m_bAbort )
		{
			break;
		}
    }
}


//--------------------------------------------------------------------------------------
// Creates the shaders in the list 
//--------------------------------------------------------------------------------------
HRESULT ShaderCache::CreateShaders()
{
    HRESULT hr = E_FAIL;
    Shader* pShader = NULL;

    for( std::list<Shader*>::iterator it = m_CreateList.begin(); it != m_CreateList.end(); it++ )
    {
        pShader = *it;

        if( NULL == *(pShader->m_ppShader) )
        {
            hr = CreateShader( pShader );
            assert( S_OK == hr );
        }
    }

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Creates a hash from a given shader
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CreateHashFromPreprocessFile( Shader* pShader )
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsPreprocessFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rt" );

    if( pFile )
    {
        fseek( pFile, SEEK_SET, SEEK_END );
        int iFileSize = ftell( pFile );
        fseek( pFile, SEEK_SET, SEEK_SET );
        char* pFileBuf = new char[iFileSize];
        fread( pFileBuf, iFileSize, 1, pFile );

        // Skip the first line of the preprocessed file, as it is only the full path to the file,
        // this cuases problems if you move a project on disk, it triggers a full rebuild of the
        // shader cache, purely because the path has changed
        char* pTemp = strchr( pFileBuf, '\n' );
        pTemp++;

        CreateHash( pTemp, iFileSize, &pShader->m_pHash, &pShader->m_uHashLength );        

        delete[] pFileBuf;
        fclose( pFile );

        return TRUE;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Creates the hash
//--------------------------------------------------------------------------------------
void ShaderCache::CreateHash( const char* data, int iFileSize, BYTE** hash, long* len )
{
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE *pbHash = NULL;
    DWORD dwHashLen = 0;

    BYTE * pbBuffer = NULL;
    DWORD dwCount = 0;
    DWORD i = 0;
    unsigned long bufLen = 0;

    // DwFlags is set to zero to attempt to open an existing key container.
    if( !CryptAcquireContext( &hProv, NULL, NULL, PROV_RSA_FULL, 0 ) ) 
    {
        // An error occurred in acquiring the context. This could mean that 
        // the key container requested does not exist. In this case, the 
        // function can be called again to attempt to create a new key container.
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            if( !CryptAcquireContext( &hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET ) ) 
            {
                return;
            }
        }
    }
    if( !CryptCreateHash( hProv, CALG_MD5, 0, 0, &hHash ) ) 
    {
        return;
    }

    bufLen = strlen( data );

    pbBuffer = (BYTE*)malloc( bufLen + 1 );
    memset( pbBuffer, 0, bufLen + 1 );

    for( i = 0; i < bufLen; i++ ) 
    {
        pbBuffer[i] = (BYTE)data[i];
    }

    if( !CryptHashData( hHash, pbBuffer, bufLen, 0 ) ) 
    {
        return;
    }

    dwCount = sizeof( DWORD );
    if( !CryptGetHashParam( hHash, HP_HASHSIZE, (BYTE *)&dwHashLen, &dwCount, 0 ) ) 
    {
        return;
    }
    
    if( ( pbHash = (unsigned char*)malloc( dwHashLen ) ) == NULL ) 
    {
        return;
    }

    memset( pbHash, 0, dwHashLen );

    if( !CryptGetHashParam( hHash, HP_HASHVAL, pbHash, &dwHashLen, 0 ) ) 
    {
        return;
    }

    *hash = pbHash;
    *len = dwHashLen;

    if( hHash )
    {
        CryptDestroyHash( hHash );
    }
    
    if( hProv ) 
    {
        CryptReleaseContext( hProv, 0 );
    }

    if( NULL != pbBuffer )
    {
        free( pbBuffer );
        pbBuffer = NULL;
    }
}


//--------------------------------------------------------------------------------------
// Writes out the hash file to disk
//--------------------------------------------------------------------------------------
void ShaderCache::WriteHashFile( Shader* pShader )
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsHashFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"wb" );

    if( pFile )
    {
        fwrite( pShader->m_pHash, pShader->m_uHashLength, 1, pFile );

        fclose( pFile );
    }
}


//--------------------------------------------------------------------------------------
// Compares a shaders hash with the has file on disk
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CompareHash( Shader* pShader )
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsHashFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rb" );

    if( pFile )
    {
        fseek( pFile, SEEK_SET, SEEK_END );
        int iFileSize = ftell( pFile );
        fseek( pFile, SEEK_SET, SEEK_SET );
        BYTE* pFileBuf = new BYTE[iFileSize];
        
        fread( pFileBuf, iFileSize, 1, pFile );

        fclose( pFile );

        if( !memcmp( pShader->m_pHash, pFileBuf, pShader->m_uHashLength ) )
        {
            delete[] pFileBuf;
            return TRUE;
        }

        delete[] pFileBuf;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Creates a shader
//--------------------------------------------------------------------------------------
HRESULT ShaderCache::CreateShader( Shader* pShader )
{
    HRESULT hr = E_FAIL;
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsObjectFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rb" );

    if( pFile )
    {
        fseek( pFile, SEEK_SET, SEEK_END );
        int iFileSize = ftell( pFile );
        fseek( pFile, SEEK_SET, SEEK_SET );
        char* pFileBuf = new char[iFileSize];
        fread( pFileBuf, iFileSize, 1, pFile );

        switch( pShader->m_eShaderType )
        {
        case SHADER_TYPE_VERTEX:
            hr = DXUTGetD3D11Device()->CreateVertexShader( pFileBuf, iFileSize, NULL, (ID3D11VertexShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            if( pShader->m_uNumDescElements )
            {
                hr = DXUTGetD3D11Device()->CreateInputLayout( pShader->m_pInputLayoutDesc, pShader->m_uNumDescElements, pFileBuf, iFileSize, pShader->m_ppInputLayout );
            }
            break;
        case SHADER_TYPE_HULL:
            hr = DXUTGetD3D11Device()->CreateHullShader( pFileBuf, iFileSize, NULL, (ID3D11HullShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            break;
        case SHADER_TYPE_DOMAIN:
            hr = DXUTGetD3D11Device()->CreateDomainShader( pFileBuf, iFileSize, NULL, (ID3D11DomainShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            break;
        case SHADER_TYPE_GEOMETRY:
            hr = DXUTGetD3D11Device()->CreateGeometryShader( pFileBuf, iFileSize, NULL, (ID3D11GeometryShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            break;
        case SHADER_TYPE_PIXEL:
            hr = DXUTGetD3D11Device()->CreatePixelShader( pFileBuf, iFileSize, NULL, (ID3D11PixelShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            break;
        case SHADER_TYPE_COMPUTE:
            hr = DXUTGetD3D11Device()->CreateComputeShader( pFileBuf, iFileSize, NULL, (ID3D11ComputeShader**)pShader->m_ppShader );
            assert( D3D_OK == hr );
            break;
        }

        delete[] pFileBuf;
        fclose( pFile );
    }

    return hr;
}


//--------------------------------------------------------------------------------------
// Compiles a shader
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CompileShader( Shader* pShader )
{
    wchar_t wsEXE[m_uPATHNAME_MAX_LENGTH];
    swprintf_s( wsEXE, L"%s%s", m_wsWorkingDir, L"\\Shaders\\fxc.exe" );
        
    SHELLEXECUTEINFO shExecInfo;
	memset( &shExecInfo, 0, sizeof( SHELLEXECUTEINFO ) );
	shExecInfo.cbSize = sizeof( SHELLEXECUTEINFO );
	shExecInfo.fMask = NULL;
	shExecInfo.hwnd = NULL;
	shExecInfo.lpFile = wsEXE;
	shExecInfo.nShow = SW_HIDE;
	shExecInfo.hInstApp = NULL;
    shExecInfo.lpParameters = pShader->m_wsCommandLine;
	BOOL bSuccess = ShellExecuteEx( &shExecInfo );

    return bSuccess;
}


//--------------------------------------------------------------------------------------
// Preprocesses a shader
//--------------------------------------------------------------------------------------
BOOL ShaderCache::PreprocessShader( Shader* pShader )
{
	wchar_t wsEXE[m_uPATHNAME_MAX_LENGTH];
	wchar_t wsUpper[m_uPATHNAME_MAX_LENGTH];
    
    // Forcing strings to upper, as the result from GetCurrentDirectoryW differs when run
    // from the debugger than when run from windows. This would make the first line of the preprocess
    // file different - for no good reason! 
    wcscpy_s( wsUpper, m_uPATHNAME_MAX_LENGTH, m_wsWorkingDir );
	_wcsupr_s( wsUpper, m_uPATHNAME_MAX_LENGTH );

    swprintf_s( wsEXE, L"%s%s", wsUpper, L"\\Shaders\\fxc.exe" );
    
    SHELLEXECUTEINFO shExecInfo;
	memset( &shExecInfo, 0, sizeof( SHELLEXECUTEINFO ) );
	shExecInfo.cbSize = sizeof( SHELLEXECUTEINFO );
	shExecInfo.fMask = NULL;
	shExecInfo.hwnd = NULL;
	shExecInfo.lpFile = wsEXE;
	shExecInfo.nShow = SW_HIDE;
	shExecInfo.hInstApp = NULL;
    shExecInfo.lpParameters = pShader->m_wsPreprocessCommandLine;
	BOOL bSuccess = ShellExecuteEx( &shExecInfo );

    return bSuccess;
}


//--------------------------------------------------------------------------------------
// Opens the error file for a given shader
//--------------------------------------------------------------------------------------
BOOL ShaderCache::OpenErrorFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsErrorFile );
    
    SHELLEXECUTEINFO shExecInfo;
	memset( &shExecInfo, 0, sizeof( SHELLEXECUTEINFO ) );
	shExecInfo.cbSize = sizeof( SHELLEXECUTEINFO );
	shExecInfo.fMask = NULL;
	shExecInfo.hwnd = NULL;
	shExecInfo.lpFile = L"notepad.exe";
	shExecInfo.nShow = SW_SHOW;
	shExecInfo.hInstApp = NULL;
    shExecInfo.lpParameters = wsShaderPathName;
	BOOL bSuccess = ShellExecuteEx( &shExecInfo );

    return bSuccess;
}


//--------------------------------------------------------------------------------------
// Checks to see if the oject file exists for a given shader
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CheckObjectFile( Shader* pShader )
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsObjectFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rt" );

    if( pFile )
    {
        fseek( pFile, SEEK_SET, SEEK_END );
        int iFileSize = ftell( pFile );
        fclose( pFile );

        if( iFileSize > 0 )
        {
            return TRUE;
        }
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Checks to see if FXC.exe is located correctly
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CheckFXC()
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s%s", m_wsWorkingDir, L"\\shaders\\fxc.exe" );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rb" );

    if( pFile )
    {
        fclose( pFile );

        return TRUE;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Checks to see if an error file exists, and opens it if non-zero in size
//--------------------------------------------------------------------------------------
BOOL ShaderCache::CheckErrorFile( Shader* pShader )
{
    FILE* pFile = NULL;
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsErrorFile );
    
    _wfopen_s( &pFile, wsShaderPathName, L"rt" );

    if( pFile )
    {
        fseek( pFile, SEEK_SET, SEEK_END );
        int iFileSize = ftell( pFile );
        
        if( iFileSize > 0 )
        {
            fseek( pFile, SEEK_SET, SEEK_SET );
            if( IsAnError( pFile ) )
            {
                fclose( pFile );
                DeleteHashFile( pShader );
                OpenErrorFile( pShader );
                _asm int 3;
            }
        }

        fclose( pFile );

        return TRUE;
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Checks an error file to see if there really was an error, rather than just a warning
//--------------------------------------------------------------------------------------
BOOL ShaderCache::IsAnError( FILE* pFile )
{
    char szLine[m_uCOMMAND_LINE_MAX_LENGTH];
    char* pLine = szLine;
    char szError[32];
    strcpy_s( szError, 32, "error" );
    
    while( fgets( pLine, m_uCOMMAND_LINE_MAX_LENGTH, pFile ) )
    {
        char* pTemp = pLine;
        while( *pTemp != '\n' )
        {
            if( !strncmp( pTemp, szError, strlen( szError ) ) )
            {
                return TRUE;
            }

            pTemp++;
        }
    }

    return FALSE;
}


//--------------------------------------------------------------------------------------
// Deletion utility method 
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteErrorFiles()
{
    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
    
        DeleteErrorFile( pShader );
    }
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteErrorFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
        
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsErrorFile );

    DeleteFile( wsShaderPathName );
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteAssemblyFiles()
{
    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
    
        DeleteAssemblyFile( pShader );
    }
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteAssemblyFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    BOOL bDeleted;
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsAssemblyFile );

    bDeleted = DeleteFile( wsShaderPathName );
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteObjectFiles()
{
    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
    
        DeleteObjectFile( pShader );
    }
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteObjectFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    BOOL bDeleted;
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsObjectFile );

    bDeleted = DeleteFile( wsShaderPathName );
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeletePreprocessFiles()
{
    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
    
        DeletePreprocessFile( pShader );
    }
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeletePreprocessFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    BOOL bDeleted;
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsPreprocessFile );

    bDeleted = DeleteFile( wsShaderPathName );
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteHashFiles()
{
    for( std::list<Shader*>::iterator it = m_ShaderList.begin(); it != m_ShaderList.end(); it++)
    {
        Shader* pShader = *it;
    
        DeleteHashFile( pShader );
    }
}


//--------------------------------------------------------------------------------------
// Deletion utility method
//--------------------------------------------------------------------------------------
void ShaderCache::DeleteHashFile( Shader* pShader )
{
    wchar_t wsShaderPathName[m_uPATHNAME_MAX_LENGTH];
    BOOL bDeleted;
    
    swprintf_s( wsShaderPathName, L"%s\\%s", m_wsWorkingDir, pShader->m_wsHashFile );

    bDeleted = DeleteFile( wsShaderPathName );
}


//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------

