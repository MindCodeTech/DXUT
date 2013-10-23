/**
 * Copyright (C) 2011 Jorge Jimenez (jorge@iryoku.com)
 * Copyright (C) 2011 Jose I. Echevarria (joseignacioechevarria@gmail.com) 
 * Copyright (C) 2011 Belen Masia (bmasia@unizar.es) 
 * Copyright (C) 2011 Fernando Navarro (fernandn@microsoft.com) 
 * Copyright (C) 2011 Diego Gutierrez (diegog@unizar.es)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the following disclaimer
 *       in the documentation and/or other materials provided with the 
 *       distribution:
 *
 *      "Uses SMAA. Copyright (C) 2011 by Jorge Jimenez, Jose I. Echevarria,
 *       Tiago Sousa, Belen Masia, Fernando Navarro and Diego Gutierrez."
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS 
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS 
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are 
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the copyright holders.
 */


#ifndef SMAA_H
#define SMAA_H

#include "DXUT.h"
#ifndef _WIN8SDK_BUILD_
#include <dxgi.h>
#include <d3d11.h>
#else
#include <dxgi1_2.h>
#include <d3d11_1.h>
#endif
#include "RenderTarget.h"
#include "Effects.h"
#include "d3dxGlobal.h"
#include "d3dx11effect.h"

/**
 * IMPORTANT NOTICE: please note that the documentation given in this file is
 * rather limited. We recommend first checking out SMAA.h in the root directory
 * of the source release (the shader header), then coming back here. This is
 * just a C++ interface to the shader.
 */

using DirectX::XMMATRIX;
using DirectX::XMFLOAT2;
namespace D3DX11Effects{}

class SMAA {
    public:
        class ExternalStorage;

        enum Mode { MODE_SMAA_1X, MODE_SMAA_T2X, MODE_SMAA_S2X, MODE_SMAA_4X };
        enum Preset { PRESET_LOW, PRESET_MEDIUM, PRESET_HIGH, PRESET_ULTRA, PRESET_CUSTOM };
        enum Input { INPUT_LUMA, INPUT_COLOR, INPUT_DEPTH };

        /**
         * By default, two render targets will be created for storing
         * intermediate calculations. If you have spare render targets,
         * search for @EXTERNAL_STORAGE.
         */
        SMAA(ID3D11Device *device, int width, int height, 
             Preset preset=PRESET_HIGH, bool predication=false, bool reprojection=false,
             const ExternalStorage &storage=ExternalStorage());
        ~SMAA();

        /**
         * Mandatory input textures varies depending on 'input':
         *    INPUT_LUMA:
         *    INPUT_COLOR:
         *        go(srcGammaSRV, srcSRV, nullptr,  depthSRV, dsv)
         *    INPUT_DEPTH:
         *        go(nullptr,     srcSRV, depthSRV, depthSRV, dsv)
         *
         * You can safely pass everything (do not use NULLs) if you want, the
         * extra paramters will be ignored accordingly. See descriptions below.
         *
         * Input texture 'depthSRV' will be used for predication if enabled. We
         * recommend using a light accumulation buffer or object ids, if
         * available; it'll probably yield better results.
         *
         * To ease implementation, everything is saved (blend state, viewport,
         * etc.), you may want to check Save*Scope in the implementation if you
         * don't need this.
         *
         * IMPORTANT: The stencil component of 'dsv' is used to mask zones to
         * be processed. It is assumed to be already cleared to zero when this
         * function is called. It is not done here because it is usually
         * cleared together with the depth.
         */
        void go(ID3D11ShaderResourceView *srcGammaSRV, // Non-SRGB version of the input color texture.
                ID3D11ShaderResourceView *srcSRV, // SRGB version of the input color texture.
                ID3D11ShaderResourceView *depthSRV, // Input depth texture.
                ID3D11RenderTargetView *dstRTV, // Output render target.
                ID3D11DepthStencilView *dsv, // Depth-stencil buffer for optimizations.
                Input input, // Selects the input for edge detection.
                Mode mode=MODE_SMAA_1X, // Selects the SMAA mode.
                int pass=0); // Selects the S2x or 4x pass (either 0 or 1).

        /**
         * This function perform a temporal resolve of two buffers. They must
         * contain temporary jittered color subsamples.
         */
        void reproject(ID3D11ShaderResourceView *currentSRV,
                       ID3D11ShaderResourceView *previousSRV,
                       ID3D11ShaderResourceView *velocitySRV,
                       ID3D11RenderTargetView *dstRTV);

        /**
         * This function separates 2 subsamples in a 2x multisampled buffer
         * (srcSRV) into two different render targets.
         */
        void separate(ID3D11ShaderResourceView *srcSRV,
                      ID3D11RenderTargetView *dst1RTV,
                      ID3D11RenderTargetView *dst2RTV);

        /**
         * Reorders the subsample indices to match the standard
         * D3D1*_STANDARD_MULTISAMPLE_PATTERN arrangement.
         * See related SMAA::detectMSAAOrder.
         */
        int msaaReorder(int sample) const { return msaaOrderMap[sample]; }

        /**
         * Threshold for the edge detection. Only has effect if PRESET_CUSTOM
         * is selected.
         */
        float getThreshold() const { return threshold; }
        void setThreshold(float threshold) { this->threshold = threshold; }

        /**
         * Maximum length to search for horizontal/vertical patterns. Each step
         * is two pixels wide. Only has effect if PRESET_CUSTOM is selected.
         */
        int getMaxSearchSteps() const { return maxSearchSteps; }
        void setMaxSearchSteps(int maxSearchSteps) { this->maxSearchSteps = maxSearchSteps; }

        /**
         * Maximum length to search for diagonal patterns. Only has effect if
         * PRESET_CUSTOM is selected.
         */
        int getMaxSearchStepsDiag() const { return maxSearchStepsDiag; }
        void setMaxSearchStepsDiag(int maxSearchStepsDiag) { this->maxSearchStepsDiag = maxSearchStepsDiag; }

        /**
         * Desired corner rounding, from 0.0 (no rounding) to 100.0 (full
         * rounding). Only has effect if PRESET_CUSTOM is selected.
         */
        float getCornerRounding() const { return cornerRounding; }
        void setCornerRounding(float cornerRounding) { this->cornerRounding = cornerRounding; }

        /**
         * These two are just for debugging purposes.
         */
        RenderTarget *getEdgesRenderTarget() { return edgesRT; }
        RenderTarget *getBlendRenderTarget() { return blendRT; }

        /**
         * Jitters the transformations matrix.
         */
        XMMATRIX JitteredMatrix(const XMMATRIX &worldViewProjection, int width, int height, Mode mode) const;

        /**
         * Increases the subpixel counter.
         */
        void nextFrame();
        int getFrameIndex() const { return frameIndex; }

        /**
         * @EXTERNAL_STORAGE
         *
         * If you have one or two spare render targets of the same size as the
         * backbuffer, you may want to pass them to SMAA::SMAA() using a
         * ExternalStorage object. You may pass one or the two, depending on
         * what you have available.
         *
         * A non-sRGB RG buffer (at least) is expected for storing edges.
         * A non-sRGB RGBA buffer is expected for the blending weights.
         */
        class ExternalStorage {
            public:
                ExternalStorage(ID3D11ShaderResourceView *edgesSRV=nullptr,
                                ID3D11RenderTargetView *edgesRTV=nullptr,
                                ID3D11ShaderResourceView *weightsSRV=nullptr,
                                ID3D11RenderTargetView *weightsRTV=nullptr)
                    : edgesSRV(edgesSRV),
                      edgesRTV(edgesRTV), 
                      weightsSRV(weightsSRV),
                      weightsRTV(weightsRTV) {}

            ID3D11ShaderResourceView *edgesSRV, *weightsSRV;
            ID3D11RenderTargetView *edgesRTV, *weightsRTV;
        };

    private:
        /**
         * Detects the sample order of MSAA 2x by rendering a quad that fills
         * the left half of a 1x1 MSAA 2x buffer. The sample #0 of this buffer
         * is then loaded and stored into a temporal 1x1 buffer. We transfer
         * this value to the CPU, and check its value to determine the actual
         * sample order. See related SMAA::msaaReorder.
         */
        void detectMSAAOrder();

        XMFLOAT2 getJitter(Mode mode) const;
        int getSubsampleIndex(Mode mode, int pass) const;

        void loadAreaTex();
        void loadSearchTex();
        void edgesDetectionPass(ID3D11DepthStencilView *dsv, Input input);
        void blendingWeightsCalculationPass(ID3D11DepthStencilView *dsv, Mode mode, int subsampleIndex);
        void neighborhoodBlendingPass(ID3D11RenderTargetView *dstRTV, ID3D11DepthStencilView *dsv);

        ID3D11Device *device;
        Preset preset;
        ID3DX11Effect *effect;
        Quad *quad;

        RenderTarget *edgesRT;
        RenderTarget *blendRT;

        ID3D11Texture2D *areaTex;
        ID3D11ShaderResourceView *areaTexSRV;
        ID3D11Texture2D *searchTex;
        ID3D11ShaderResourceView *searchTexSRV;

        ID3DX11EffectScalarVariable *thresholdVariable, *cornerRoundingVariable,
                                   *maxSearchStepsVariable, *maxSearchStepsDiagVariable,
                                   *blendFactorVariable;
        ID3DX11EffectVectorVariable *subsampleIndicesVariable;
        ID3DX11EffectShaderResourceVariable *areaTexVariable, *searchTexVariable,
                                           *colorTexVariable, *colorTexGammaVariable, *colorTexPrevVariable, *colorMSTexVariable,
                                           *depthTexVariable, *velocityTexVariable,
                                           *edgesTexVariable, *blendTexVariable;

        ID3DX11EffectTechnique *edgeDetectionTechniques[3],
                              *blendingWeightCalculationTechnique,
                              *neighborhoodBlendingTechnique,
                              *resolveTechnique,
                              *separateTechnique;

        float threshold, cornerRounding;
        int maxSearchSteps, maxSearchStepsDiag;

        int frameIndex;
        int msaaOrderMap[2];
};

#endif
