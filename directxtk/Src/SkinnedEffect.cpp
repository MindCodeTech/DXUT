//--------------------------------------------------------------------------------------
// File: SkinnedEffect.cpp
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


#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

// Constant buffer layout. Must match the shader!
struct DXTKAPI SkinnedEffectConstants
{
    XMVECTOR diffuseColor;
    XMVECTOR emissiveColor;
    XMVECTOR specularColorAndPower;
    
    XMVECTOR lightDirection[IEffectLights::MaxDirectionalLights];
    XMVECTOR lightDiffuseColor[IEffectLights::MaxDirectionalLights];
    XMVECTOR lightSpecularColor[IEffectLights::MaxDirectionalLights];

    XMVECTOR eyePosition;

    XMVECTOR fogColor;
    XMVECTOR fogVector;

    XMMATRIX world;
    XMVECTOR worldInverseTranspose[3];
    XMMATRIX worldViewProj;

    XMVECTOR bones[SkinnedEffect::MaxBones][3];
};


// Traits type describes our characteristics to the EffectBase template.
struct DXTKAPI SkinnedEffectTraits
{
    typedef SkinnedEffectConstants ConstantBufferType;

    static const int VertexShaderCount = 9;
    static const int PixelShaderCount = 3;
    static const int ShaderPermutationCount = 18;
};


// Internal SkinnedEffect implementation class.
class DXTKAPI  SkinnedEffect::Impl : public EffectBase<SkinnedEffectTraits>
{
public:
    Impl(_In_ ID3D11Device* device);

    bool preferPerPixelLighting;
    int weightsPerVertex;

    EffectLights lights;

    int GetCurrentShaderPermutation();

    void Apply(_In_ ID3D11DeviceContext* deviceContext);
};


// Include the precompiled shader code.
namespace
{
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedVertexLightingOneBone.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedVertexLightingTwoBones.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedVertexLightingFourBones.inc"

    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedOneLightOneBone.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedOneLightTwoBones.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedOneLightFourBones.inc"

    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedPixelLightingOneBone.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedPixelLightingTwoBones.inc"
    #include "Shaders/Compiled/SkinnedEffect_VSSkinnedPixelLightingFourBones.inc"

    #include "Shaders/Compiled/SkinnedEffect_PSSkinnedVertexLighting.inc"
    #include "Shaders/Compiled/SkinnedEffect_PSSkinnedVertexLightingNoFog.inc"
    #include "Shaders/Compiled/SkinnedEffect_PSSkinnedPixelLighting.inc"
}


const ShaderBytecode EffectBase<SkinnedEffectTraits>::VertexShaderBytecode[] =
{
    { SkinnedEffect_VSSkinnedVertexLightingOneBone,   sizeof(SkinnedEffect_VSSkinnedVertexLightingOneBone)   },
    { SkinnedEffect_VSSkinnedVertexLightingTwoBones,  sizeof(SkinnedEffect_VSSkinnedVertexLightingTwoBones)  },
    { SkinnedEffect_VSSkinnedVertexLightingFourBones, sizeof(SkinnedEffect_VSSkinnedVertexLightingFourBones) },

    { SkinnedEffect_VSSkinnedOneLightOneBone,         sizeof(SkinnedEffect_VSSkinnedOneLightOneBone)         },
    { SkinnedEffect_VSSkinnedOneLightTwoBones,        sizeof(SkinnedEffect_VSSkinnedOneLightTwoBones)        },
    { SkinnedEffect_VSSkinnedOneLightFourBones,       sizeof(SkinnedEffect_VSSkinnedOneLightFourBones)       },

    { SkinnedEffect_VSSkinnedPixelLightingOneBone,    sizeof(SkinnedEffect_VSSkinnedPixelLightingOneBone)    },
    { SkinnedEffect_VSSkinnedPixelLightingTwoBones,   sizeof(SkinnedEffect_VSSkinnedPixelLightingTwoBones)   },
    { SkinnedEffect_VSSkinnedPixelLightingFourBones,  sizeof(SkinnedEffect_VSSkinnedPixelLightingFourBones)  },
};


const int EffectBase<SkinnedEffectTraits>::VertexShaderIndices[] =
{
    0,      // vertex lighting, one bone
    0,      // vertex lighting, one bone, no fog
    1,      // vertex lighting, two bones
    1,      // vertex lighting, two bones, no fog
    2,      // vertex lighting, four bones
    2,      // vertex lighting, four bones, no fog
    
    3,      // one light, one bone
    3,      // one light, one bone, no fog
    4,      // one light, two bones
    4,      // one light, two bones, no fog
    5,      // one light, four bones
    5,      // one light, four bones, no fog
    
    6,      // pixel lighting, one bone
    6,      // pixel lighting, one bone, no fog
    7,      // pixel lighting, two bones
    7,      // pixel lighting, two bones, no fog
    8,      // pixel lighting, four bones
    8,      // pixel lighting, four bones, no fog
};


const ShaderBytecode EffectBase<SkinnedEffectTraits>::PixelShaderBytecode[] =
{
    { SkinnedEffect_PSSkinnedVertexLighting,      sizeof(SkinnedEffect_PSSkinnedVertexLighting)      },
    { SkinnedEffect_PSSkinnedVertexLightingNoFog, sizeof(SkinnedEffect_PSSkinnedVertexLightingNoFog) },
    { SkinnedEffect_PSSkinnedPixelLighting,       sizeof(SkinnedEffect_PSSkinnedPixelLighting)       },
};


const int EffectBase<SkinnedEffectTraits>::PixelShaderIndices[] =
{
    0,      // vertex lighting, one bone
    1,      // vertex lighting, one bone, no fog
    0,      // vertex lighting, two bones
    1,      // vertex lighting, two bones, no fog
    0,      // vertex lighting, four bones
    1,      // vertex lighting, four bones, no fog
    
    0,      // one light, one bone
    1,      // one light, one bone, no fog
    0,      // one light, two bones
    1,      // one light, two bones, no fog
    0,      // one light, four bones
    1,      // one light, four bones, no fog
    
    2,      // pixel lighting, one bone
    2,      // pixel lighting, one bone, no fog
    2,      // pixel lighting, two bones
    2,      // pixel lighting, two bones, no fog
    2,      // pixel lighting, four bones
    2,      // pixel lighting, four bones, no fog
};


// Global pool of per-device SkinnedEffect resources.
SharedResourcePool<ID3D11Device*, EffectBase<SkinnedEffectTraits>::DeviceResources> EffectBase<SkinnedEffectTraits>::deviceResourcesPool;


// Constructor.
DXTKAPI  SkinnedEffect::Impl::Impl(_In_ ID3D11Device* device)
  : EffectBase(device),
    preferPerPixelLighting(false),
    weightsPerVertex(4)
{
    lights.InitializeConstants(constants.specularColorAndPower, constants.lightDirection, constants.lightDiffuseColor, constants.lightSpecularColor);

    for (int i = 0; i < MaxBones; i++)
    {
        constants.bones[i][0] = g_XMIdentityR0;
        constants.bones[i][1] = g_XMIdentityR1;
        constants.bones[i][2] = g_XMIdentityR2;
    }
}


DXTKAPI  int SkinnedEffect::Impl::GetCurrentShaderPermutation()
{
    int permutation = 0;

    // Use optimized shaders if fog is disabled.
    if (!fog.enabled)
    {
        permutation += 1;
    }

    // Evaluate 1, 2, or 4 weights per vertex?
    if (weightsPerVertex == 2)
    {
        permutation += 2;
    }
    else if (weightsPerVertex == 4)
    {
        permutation += 4;
    }

    if (preferPerPixelLighting)
    {
        // Do lighting in the pixel shader.
        permutation += 12;
    }
    else if (!lights.lightEnabled[1] && !lights.lightEnabled[2])
    {
        // Use the only-bother-with-the-first-light shader optimization.
        permutation += 6;
    }

    return permutation;
}


// Sets our state onto the D3D device.
DXTKAPI  void SkinnedEffect::Impl::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
    // Compute derived parameter values.
    matrices.SetConstants(dirtyFlags, constants.worldViewProj);

    fog.SetConstants(dirtyFlags, matrices.worldView, constants.fogVector);
            
    lights.SetConstants(dirtyFlags, matrices, constants.world, constants.worldInverseTranspose, constants.eyePosition, constants.diffuseColor, constants.emissiveColor, true);

    // Set the texture.
    ID3D11ShaderResourceView* textures[1] = { texture.Get() };

    deviceContext->PSSetShaderResources(0, 1, textures);
    
    // Set shaders and constant buffers.
    ApplyShaders(deviceContext, GetCurrentShaderPermutation());
}


// Public constructor.
DXTKAPI  SkinnedEffect::SkinnedEffect(_In_ ID3D11Device* device)
  : pImpl(new Impl(device))
{
}


// Move constructor.
DXTKAPI  SkinnedEffect::SkinnedEffect(SkinnedEffect&& moveFrom)
  : pImpl(std::move(moveFrom.pImpl))
{
}


// Move assignment.
DXTKAPI  SkinnedEffect& SkinnedEffect::operator= (SkinnedEffect&& moveFrom)
{
    pImpl = std::move(moveFrom.pImpl);
    return *this;
}


// Public destructor.
DXTKAPI  SkinnedEffect::~SkinnedEffect()
{
}


DXTKAPI  void SkinnedEffect::Apply(_In_ ID3D11DeviceContext* deviceContext)
{
    pImpl->Apply(deviceContext);
}


DXTKAPI  void SkinnedEffect::GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)
{
    pImpl->GetVertexShaderBytecode(pImpl->GetCurrentShaderPermutation(), pShaderByteCode, pByteCodeLength);
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetWorld(FXMMATRIX value)
{
    pImpl->matrices.world = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::WorldInverseTranspose | EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetView(FXMMATRIX value)
{
    pImpl->matrices.view = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetProjection(FXMMATRIX value)
{
    pImpl->matrices.projection = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetDiffuseColor(FXMVECTOR value)
{
    pImpl->lights.diffuseColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetEmissiveColor(FXMVECTOR value)
{
    pImpl->lights.emissiveColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetSpecularColor(FXMVECTOR value)
{
    // Set xyz to new value, but preserve existing w (specular power).
    pImpl->constants.specularColorAndPower = XMVectorSelect(pImpl->constants.specularColorAndPower, value, g_XMSelect1110);

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


DXTKAPI  void SkinnedEffect::SetSpecularPower(float value)
{
    // Set w to new value, but preserve existing xyz (specular color).
    pImpl->constants.specularColorAndPower = XMVectorSetW(pImpl->constants.specularColorAndPower, value);

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


DXTKAPI  void SkinnedEffect::SetAlpha(float value)
{
    pImpl->lights.alpha = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void SkinnedEffect::SetLightingEnabled(bool value)
{
    if (!value)
    {
        throw std::exception("SkinnedEffect does not support turning off lighting");
    }
}


DXTKAPI  void SkinnedEffect::SetPerPixelLighting(bool value)
{
    pImpl->preferPerPixelLighting = value;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetAmbientLightColor(FXMVECTOR value)
{
    pImpl->lights.ambientLightColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::MaterialColor;
}


DXTKAPI  void SkinnedEffect::SetLightEnabled(int whichLight, bool value)
{
    pImpl->dirtyFlags |= pImpl->lights.SetLightEnabled(whichLight, value, pImpl->constants.lightDiffuseColor, pImpl->constants.lightSpecularColor);
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetLightDirection(int whichLight, FXMVECTOR value)
{
    EffectLights::ValidateLightIndex(whichLight);

    pImpl->constants.lightDirection[whichLight] = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetLightDiffuseColor(int whichLight, FXMVECTOR value)
{
    pImpl->dirtyFlags |= pImpl->lights.SetLightDiffuseColor(whichLight, value, pImpl->constants.lightDiffuseColor);
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetLightSpecularColor(int whichLight, FXMVECTOR value)
{
    pImpl->dirtyFlags |= pImpl->lights.SetLightSpecularColor(whichLight, value, pImpl->constants.lightSpecularColor);
}


DXTKAPI  void SkinnedEffect::EnableDefaultLighting()
{
    EffectLights::EnableDefaultLighting(this);
}


DXTKAPI  void SkinnedEffect::SetFogEnabled(bool value)
{
    pImpl->fog.enabled = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogEnable;
}


DXTKAPI  void SkinnedEffect::SetFogStart(float value)
{
    pImpl->fog.start = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogVector;
}


DXTKAPI  void SkinnedEffect::SetFogEnd(float value)
{
    pImpl->fog.end = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::FogVector;
}


DXTKAPI  void XM_CALLCONV SkinnedEffect::SetFogColor(FXMVECTOR value)
{
    pImpl->constants.fogColor = value;

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


DXTKAPI  void SkinnedEffect::SetTexture(_In_opt_ ID3D11ShaderResourceView* value)
{
    pImpl->texture = value;
}


DXTKAPI  void SkinnedEffect::SetWeightsPerVertex(int value)
{
    if ((value != 1) &&
        (value != 2) &&
        (value != 4))
    {
        throw std::out_of_range("WeightsPerVertex must be 1, 2, or 4");
    }

    pImpl->weightsPerVertex = value;
}


DXTKAPI  void SkinnedEffect::SetBoneTransforms(_In_reads_(count) XMMATRIX const* value, size_t count)
{
    if (count > MaxBones)
        throw std::out_of_range("count parameter out of range");

    auto boneConstant = pImpl->constants.bones;

    for (size_t i = 0; i < count; i++)
    {
        XMMATRIX boneMatrix = XMMatrixTranspose(value[i]);

        boneConstant[i][0] = boneMatrix.r[0];
        boneConstant[i][1] = boneMatrix.r[1];
        boneConstant[i][2] = boneMatrix.r[2];
    }

    pImpl->dirtyFlags |= EffectDirtyFlags::ConstantBuffer;
}


#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif

