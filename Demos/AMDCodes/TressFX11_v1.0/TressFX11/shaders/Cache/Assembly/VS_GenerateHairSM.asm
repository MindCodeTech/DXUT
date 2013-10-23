//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /T vs_5_0 /O1 /E VS_GenerateHairSM shaders\Source\hairBasic.hlsl /Fo
//    Shaders\Cache\Object\Release\VS_GenerateHairSM.obj /Fe
//    Shaders\Cache\Error\VS_GenerateHairSM.txt /Fc
//    Shaders\Cache\Assembly\VS_GenerateHairSM.asm
//
//
// Buffer Definitions: 
//
// cbuffer cbPerFrame
// {
//
//   float4x4 g_mWorld;                 // Offset:    0 Size:    64 [unused]
//   float4x4 g_mViewProj;              // Offset:   64 Size:    64 [unused]
//   float4x4 g_mInvViewProj;           // Offset:  128 Size:    64 [unused]
//   float4x4 g_mViewProjLight;         // Offset:  192 Size:    64
//   float3 g_vEye;                     // Offset:  256 Size:    12 [unused]
//   float g_fvFov;                     // Offset:  268 Size:     4 [unused]
//   float4 g_AmbientLightColor;        // Offset:  272 Size:    16 [unused]
//   float4 g_PointLightColor;          // Offset:  288 Size:    16 [unused]
//   float4 g_PointLightPos;            // Offset:  304 Size:    16 [unused]
//   float4 g_MatBaseColor;             // Offset:  320 Size:    16 [unused]
//   float4 g_MatKValue;                // Offset:  336 Size:    16 [unused]
//   float g_FiberAlpha;                // Offset:  352 Size:     4 [unused]
//   float g_HairShadowAlpha;           // Offset:  356 Size:     4 [unused]
//   float g_bExpandPixels;             // Offset:  360 Size:     4 [unused]
//   float g_FiberRadius;               // Offset:  364 Size:     4 [unused]
//   float g_fHairKs2;                  // Offset:  368 Size:     4 [unused]
//   float g_fHairEx2;                  // Offset:  372 Size:     4 [unused]
//   float2 g_WinSize;                  // Offset:  376 Size:     8 [unused]
//   float g_FiberSpacing;              // Offset:  384 Size:     4 [unused]
//   float g_bThinTip;                  // Offset:  388 Size:     4 [unused]
//   float g_fNearLight;                // Offset:  392 Size:     4 [unused]
//   float g_fFarLight;                 // Offset:  396 Size:     4 [unused]
//   int g_iTechSM;                     // Offset:  400 Size:     4 [unused]
//   int g_bUseCoverage;                // Offset:  404 Size:     4 [unused]
//   int g_bUseAltCoverage;             // Offset:  408 Size:     4 [unused]
//   int g_iStrandCopies;               // Offset:  412 Size:     4 [unused]
//
// }
//
// Resource bind info for g_GuideHairVertexPositions
// {
//
//   float4 $Element;                   // Offset:    0 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_GuideHairVertexPositions        texture  struct         r/o    8        1
// cbPerFrame                        cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// POSITION                 0   xyz         0     NONE  float       
// TANGENT                  0   xyz         1     NONE  float       
// TEXCOORD                 0   xyzw        2     NONE  float       
// SV_VERTEXID              0   x           3   VERTID   uint   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float   xyzw
// TEXCOORD                 0   xyz         1     NONE  float   xyz 
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[16], immediateIndexed
dcl_resource_structured t8, 16 
dcl_input_sgv v3.x, vertex_id
dcl_output_siv o0.xyzw, position
dcl_output o1.xyz
dcl_temps 1
mov r0.w, l(1.000000)
ld_structured_indexable(structured_buffer, stride=16)(mixed,mixed,mixed,mixed) r0.xyz, v3.x, l(0), t8.xyzx
dp4 o0.x, r0.xyzw, cb0[12].xyzw
dp4 o0.y, r0.xyzw, cb0[13].xyzw
dp4 o0.z, r0.xyzw, cb0[14].xyzw
dp4 o0.w, r0.xyzw, cb0[15].xyzw
mov o1.xyz, r0.xyzx
ret 
// Approximately 8 instruction slots used