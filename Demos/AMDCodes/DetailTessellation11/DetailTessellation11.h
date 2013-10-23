//--------------------------------------------------------------------------------------
// File: DX11TessellationTest.h
//
// Copyright (c) AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef DX11TESSELLATIONTEST_H
#define DX11TESSELLATIONTEST_H

struct SIMPLEVERTEX 
{
        FLOAT x, y, z;
        FLOAT u, v;
};

struct EXTENDEDVERTEX 
{
        FLOAT x, y, z;
        FLOAT nx, ny, nz;
        FLOAT u, v;
};

struct TANGENTSPACEVERTEX 
{
        FLOAT x, y, z;
        FLOAT u, v;
        FLOAT nx, ny, nz;
        FLOAT bx, by, bz;
        FLOAT tx, ty, tz;
};


#endif
