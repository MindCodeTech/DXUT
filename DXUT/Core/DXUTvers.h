//--------------------------------------------------------------------------------------
// File: DXUTvers.h
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

#define DXUTLIB_VERSION_DATE "2013.11.19"

// I have defined to version 8 in reference to windows 8 but we can change-it !!(I cant find info about DXUT version)
#define DXUTLIB_VERSION "11.0.4"
#define DXUTLIB_VERNUM 0x11040
#define DXUTLIB_VER_MAJOR 11
#define DXUTLIB_VER_MINOR 0
#define DXUTLIB_VER_REVISION 4
#define DXUTLIB_VER_SUBREVISION 0

#define DXUTLIB_VERSION_STR DXUTLIB_VER_MAJOR, DXUTLIB_VER_MINOR, DXUTLIB_VER_REVISION, DXUTLIB_VER_SUBREVISION

#ifdef _DEBUG
#define DXUTLIB_BUILD_ "_d"
#else
#define DXUTLIB_BUILD_ ""
#endif
