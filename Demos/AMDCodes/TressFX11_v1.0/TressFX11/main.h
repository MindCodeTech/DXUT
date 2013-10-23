//--------------------------------------------------------------------------------------
// File: main.h
//
// Header file for main
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "..\\DXUT\\Core\\DXUT.h"
// AMD SDK 
#include "..\\AMD_SDK\\AMD_SDK.h"


extern D3DXMATRIX g_ModelTransform;
extern D3DXMATRIX g_ModelTransformForHead;
extern D3DXMATRIX g_ModelPrevInvTransformForHead;
extern bool g_bModelTransformUpdated;

extern D3DXVECTOR3 g_HairColor;

extern AMD::ShaderCache     g_ShaderCache; 