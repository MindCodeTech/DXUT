//--------------------------------------------------------------------------------------
// File: DualTextureEffect.cpp
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
#include "pch.h"
#include "EffectCommon.h"

using namespace DirectX;
using namespace Microsoft::WRL;

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

// Constant buffer layout. Must match the shader!
struct DXTKAPI DualTextureEffectConstants
{
    XMVECTOR diffuseColor;
    XMVECTOR fogColor;
    XMVECTOR fogVector;
    XMMATRIX worldViewProj;
};


// Traits type describes our characteristics to the EffectBase template.
struct DXTKAPI DualTextureEffectTraits
{
    typedef DualTextureEffectConstants ConstantBufferType;

    static const int VertexShaderCount = 4;
    static const int PixelShaderCount = 2;
    static const int ShaderPermutationCount = 4;
};


// Internal DualTextureEffect implementation class.
class DXTKAPI  DualTextureEffect::Impl : public EffectBase<DualTextureEffectTraits>
{
public:
    Impl(_In_ ID3D11Device* device);

    bool vertexColorEnabled;
    
    EffectColor color;

    ComPtr<ID3D11ShaderResourceView> texture2;

    int GetCurrentShaderPermutation();

    void Apply(_In_ ID3D11DeviceContext* deviceContext);
};


// Include the precompiled shader code.
namespace
{
    #include "Shaders/Compiled/DualTextureEffect_VSDualTexture.inc"
    #include "Shaders/Compiled/DualTextureEffect_VSDualTextureNoFog.inc"
    #include "Shaders/Compiled/DualTextureEffect_VSDualTextureVc.inc"
    #include "Shaders/Compiled/DualTextureEffect_VSDualTextureVcNoFog.inc"

    #include "Shaders/Compiled/DualTextureEffect_PSDualTexture.inc"
    #include "Shaders/Compiled/DualTextureEffect_PSDualTextureNoFog.inc"
}


const ShaderBytecode EffectBase<DualTextureEffectTraits>::VertexShaderBytecode[] =
{
    { DualTextureEffect_VSDualTexture,        sizeof(DualTextureEffect_VSDualTexture)        },
    { DualTextureEffect_VSDualTextureNoFog,   sizeof(DualTextureEffect_VSDualTextureNoFog)   },
    { DualTextureEffect_VSDualTextureVc,      sizeof(DualTextureEffect_VSDualTextureVc)      },
    { DualTextureEffect_VSDualTextureVcNoFog, sizeof(DualTextureEffect_VSDualTextureVcNoFog) },

};


const int EffectBase<DualTextureEffectTraits>::VertexShaderIndices[] =
{
    0,      // basic
    1,      // no fog
    2,      // vertex color
    3,      // vertex color, no fog
};


const ShaderBytecode EffectBase<DualTextureEffectTraits>::PixelShaderBytecode[] =
{
    { DualTextureEffect_PSDualTexture,        sizeof(DualTextureEffect_PSDualTexture)        },
    { DualTextureEffect_PSDualTextureNoFog,   sizeof(DualTextureEffect_PSDualTextureNoFog)   },

};


const int EffectBase<DualTextureEffectTraits>::PixelShaderIndices[] =
{
    0,      // basic
    1,      // no fog
    0,      // vertex color
    1,      // vertex color, no fog
};


// Global pool of per-device DualTextureEffect resources.
DXTKAPI  SharedResourcePool<ID3D11Device*, EffectBase<DualTextureEffectTraits>::DeviceResources> EffectBase<DualTextureEffectTraits>::deviceResourcesPool;


// Constructor.
DXTKAPI  DualTextureEffect::Impl::Impl(_In_ ID3D11Device* device)
  : EffectBase(device),
    vertexColorEnabled(false)
{
}


DXTKAPI  int DualTextureEffect::Impl::GetCurrentShaderPermutation()
{
    int permutation = 0;

    // Use optimized shaders if fog is disabled.
    if (!fog.enabled)
    {
        permutation += 1;
    }

    // Support vertex coloring?
    if (vertexColorEnabled)
    {
        permutation += 2;
    }

    return permutation;
}


// Sets our state onto the D3D device.
DXTKAPI  void DualTextureEffect::Impl::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
    // Compute derived parameter values.
    matrices.SetConstants(dirtyFlags, constants.worldViewProj);

    fog.SetConstants(dirtyFlags, matrices.worldView, constants.fogVector);

    color.SetConstants(dirtyFlags, constants.diffuseColor);

    // Set the textures.
    ID3D11ShaderResourceView* textures[2] =
    {
        texture.Get(),
        texture2.Get(),
    };

    deviceContext->PSSetShaderResources(0, 2, textures);
    
    // Set shaders and constant buffers.
    ApplyShaders(deviceContext, GetCurrentShaderPermutation());
}


// Public constructor.
DXTKAPI  DualTextureEffect::DualTextureEffect(_In_ ID3D11Device* device)
  : pImpl(new Impl(device))
{
}


// Move constructor.
DXTKAPI  DualTextureEffect::DualTextureEffect(DualTextureEffect&& moveFrom)
  : pImpl(std::move(moveFrom.pImpl))
{
}


// Move assignment.
DXTKAPI  DualTextureEffect& DualTextureEffect::operator= (DualTextureEffect&& moveFrom)
{
    pImpl = std::move(moveFrom.pImpl);
    return *this;
}


// Public destructor.
DXTKAPI  DualTextureEffect::~DualTextureEffect()
{
}


DXTKAPI  void DualTextureEffect::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
    pImpl->Apply(deviceContext);
}


DXTKAPI  void DualTextureEffect::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
    pImpl->GetVertexShaderBytecode(pImpl->GetCurrentShaderPermutation(), pShaderByteCode, pByteCodeLength);
}


DXTKAPI  void XM_CALLCONV DualTextureEffect::SetWorld(FXMMATRIX value)
{
    pImpl->matrices.world = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::WorldInverseTranspose | EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV DualTextureEffect::SetView(FXMMATRIX value)
{
    pImpl->matrices.view = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV DualTextureEffect::SetProjection(FXMMATRIX value)
{
    pImpl->matrices.projection = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
}


DXTKAPI  void XM_CALLCONV DualTextureEffect::SetDiffuseColor(FXMVECTOR value)
{
    pImpl->color.diffuseColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void DualTextureEffect::SetAlpha(float value)
{
    pImpl->color.alpha = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void DualTextureEffect::SetFogEnabled(bool value)
{
    pImpl->fog.enabled = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogEnable;
}


DXTKAPI  void DualTextureEffect::SetFogStart(float value)
{
    pImpl->fog.start = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogVector;
}


DXTKAPI  void DualTextureEffect::SetFogEnd(float value)
{
    pImpl->fog.end = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV DualTextureEffect::SetFogColor(FXMVECTOR value)
{
    pImpl->constants.fogColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


DXTKAPI  void DualTextureEffect::SetVertexColorEnabled(bool value)
{
    pImpl->vertexColorEnabled = value;
}


DXTKAPI  void DualTextureEffect::SetTexture(_In_opt_ ID3D11ShaderResourceView* value)
{
    pImpl->texture = value;
}


DXTKAPI  void DualTextureEffect::SetTexture2(_In_opt_ ID3D11ShaderResourceView* value)
{
    pImpl->texture2 = value;
}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
