//--------------------------------------------------------------------------------------
// File: ShaderCache.h
//
// Class definition for the ShaderCache interface. Allows the user to add shaders to a list
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


#pragma once

#include <list>
#include <vector>

namespace AMD
{

class ShaderCache
{
public:

    // Constants used for string size limits
    static const int m_uCOMMAND_LINE_MAX_LENGTH = 1024;
    static const int m_uTARGET_MAX_LENGTH = 16;
    static const int m_uENTRY_POINT_MAX_LENGTH = 128;
    static const int m_uFILENAME_MAX_LENGTH = 256;
    static const int m_uPATHNAME_MAX_LENGTH = 512;
    static const int m_uMACRO_MAX_LENGTH = 64;

    // Shader type enumeration
    typedef enum _SHADER_TYPE
    {
        SHADER_TYPE_VERTEX,
        SHADER_TYPE_HULL,
        SHADER_TYPE_DOMAIN,
        SHADER_TYPE_GEOMETRY,
        SHADER_TYPE_PIXEL,
        SHADER_TYPE_COMPUTE,
        SHADER_TYPE_UNKNOWN,
        SHADER_TYPE_MAX
    }SHADER_TYPE;

    // Create type enumeration
    typedef enum _CREATE_TYPE
    {
        CREATE_TYPE_FORCE_COMPILE,      // Clean the cache, and compile all
        CREATE_TYPE_COMPILE_CHANGES,    // Only compile shaders that have changed (development mode)
        CREATE_TYPE_USE_CACHED,         // Use cached shaders (release mode)
        CREATE_TYPE_MAX
    }CREATE_TYPE;

    // The Macro structure 
    class Macro
    {
    public:

        wchar_t             m_wsName[m_uMACRO_MAX_LENGTH];
        int                 m_iValue;
    };

    // The shader class
    class Shader
    {
    public:

        Shader();
        ~Shader();

        SHADER_TYPE                 m_eShaderType;
        ID3D11DeviceChild**         m_ppShader;
        ID3D11InputLayout**         m_ppInputLayout;
        D3D11_INPUT_ELEMENT_DESC*   m_pInputLayoutDesc;
        unsigned int                m_uNumDescElements;
        wchar_t                     m_wsTarget[m_uTARGET_MAX_LENGTH];
        wchar_t                     m_wsEntryPoint[m_uENTRY_POINT_MAX_LENGTH];
        wchar_t                     m_wsSourceFile[m_uFILENAME_MAX_LENGTH];
        unsigned int                m_uNumMacros;
        Macro*                      m_pMacros;
        wchar_t                     m_wsObjectFile[m_uFILENAME_MAX_LENGTH];
        wchar_t                     m_wsErrorFile[m_uFILENAME_MAX_LENGTH];
        wchar_t                     m_wsAssemblyFile[m_uFILENAME_MAX_LENGTH];
        wchar_t                     m_wsPreprocessFile[m_uFILENAME_MAX_LENGTH];
        wchar_t                     m_wsHashFile[m_uFILENAME_MAX_LENGTH];
        wchar_t                     m_wsCommandLine[m_uCOMMAND_LINE_MAX_LENGTH];
        wchar_t                     m_wsPreprocessCommandLine[m_uCOMMAND_LINE_MAX_LENGTH];
        bool                        m_bBeingProcessed;
        BYTE*                       m_pHash;
        long                        m_uHashLength;
    };

    // Construction / destruction
    ShaderCache();
    ~ShaderCache();

    // Allows the user to add a shader to the cache
    bool AddShader( ID3D11DeviceChild** ppShader, 
                    SHADER_TYPE ShaderType, 
                    const wchar_t* pwsTarget, 
                    const wchar_t* pwsEntryPoint, 
                    const wchar_t* pwsSourceFile,
                    unsigned int uNumMacros, 
                    Macro* pMacros,
                    ID3D11InputLayout** ppInputLayout,
                    const D3D11_INPUT_ELEMENT_DESC* pLayout,
                    unsigned int uNumElements );

    // Allows the user to generate shaders added to the cache
    HRESULT GenerateShaders( CREATE_TYPE CreateType );
    
    // Renders the progress of the shader generation
    void RenderProgress( CDXUTTextHelper* g_pTxtHelper, int iFontHeight, D3DXCOLOR FontColor );

    // User can enquire to see if shaders are ready
    bool ShadersReady();

	// DXUT framework hook method (flags the shaders as needing creating)
	void OnDestroyDevice();

	// Called by app when WM_QUIT is posted, so that shader generation can be aborted
	void Abort();

	// Called by the app to override optimizations when compiling shaders in release mode
	void ForceDebugShaders( bool bForce ) { m_bForceDebugShaders = bForce; }

    // Do not call this function
    void GenerateShadersThreadProc();

private:

    // Preprocessing, compilation, and creation methods
    void PreprocessShaders();
    void CompileShaders();
    HRESULT CreateShaders();
    BOOL PreprocessShader( Shader* pShader );
    BOOL CompileShader( Shader* pShader );
    HRESULT CreateShader( Shader* pShader );
    
    // Hash methods
    BOOL CreateHashFromPreprocessFile( Shader* pShader );
    void CreateHash( const char* data, int iFileSize, BYTE** hash, long* len );
    void WriteHashFile( Shader* pShader );
    BOOL CompareHash( Shader* pShader );

    // Check methods
    BOOL CheckFXC();
    BOOL CheckObjectFile( Shader* pShader );
    BOOL CheckErrorFile( Shader* pShader );
    BOOL IsAnError( FILE* pFile );
    
    // Opens the error file
    BOOL OpenErrorFile( Shader* pShader );
    
    // Various delete methods
    void DeleteErrorFiles();
    void DeleteErrorFile( Shader* pShader );
    void DeleteAssemblyFiles();
    void DeleteAssemblyFile( Shader* pShader );
    void DeleteObjectFiles();
    void DeleteObjectFile( Shader* pShader );
    void DeletePreprocessFiles();
    void DeletePreprocessFile( Shader* pShader );
    void DeleteHashFiles();
    void DeleteHashFile( Shader* pShader );

    // Private data
    CREATE_TYPE             m_CreateType;
    unsigned int            m_uNumCPUCores;
    bool                    m_bShadersCreated;
	bool					m_bAbort;
    bool                    m_bPrintedProgress;
    std::list<Shader*>      m_ShaderList;
    std::list<Shader*>      m_PreprocessList;
    std::list<Shader*>      m_CompileList;
    std::list<Shader*>      m_CreateList;
    wchar_t**               m_ppProgressStrings;
    unsigned int            m_uProgressCounter;
	wchar_t					m_wsWorkingDir[m_uPATHNAME_MAX_LENGTH];
	bool					m_bForceDebugShaders;
};

}; // namespace AMD


//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------
