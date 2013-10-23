//--------------------------------------------------------------------------------------
// File: DirectXTexvers.h
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

#define DXTEXLIB_VERSION_DATE "2013.10.16"

// I have defined to version 8 in reference to windows 8 but we can change-it !!(I cant find info about DXTEX version)
#define DXTEXLIB_VERSION "8.0.0"
#define DXTEXLIB_VERNUM 0x8000
#define DXTEXLIB_VER_MAJOR 8
#define DXTEXLIB_VER_MINOR 0
#define DXTEXLIB_VER_REVISION 0
#define DXTEXLIB_VER_SUBREVISION 0

#define DXTEXLIB_VERSION_STR DXTEXLIB_VER_MAJOR, DXTEXLIB_VER_MINOR, DXTEXLIB_VER_REVISION, DXTEXLIB_VER_SUBREVISION

#ifdef _DEBUG
#define DXTEXLIB_BUILD_ "d"
#else
#define DXTEXLIB_BUILD_ ""
#endif
