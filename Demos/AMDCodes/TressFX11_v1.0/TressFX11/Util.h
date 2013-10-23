//--------------------------------------------------------------------------------------
// File: Util.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <fstream>
using std::ostream;
//using std::ifstream;

#include <string.h>
#include <string>
using std::string;

#include <vector>
using std::vector;
using std::swap;

//#include "sceneparams.h"

typedef double StatsCounterType;

#define EPSILON 0.00001f

#define RAY_EPSILON 1e-3f
#define INFINITY FLT_MAX
#define Assert(condition, message) (condition? (void)0 : MessageBoxW(0, L"Error", message, 0))

#if defined(WIN32)
#define memalign(a,b) _aligned_malloc(b, a)
#elif defined(__APPLE__)
#define memalign(a,b) valloc(b)
#elif defined(__OpenBSD__)
#define memalign(a,b) malloc(b)
#endif

void *AllocAligned(size_t size);
void FreeAligned(void *ptr);

float Log2(float x);



struct StandardVertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;
    D3DXVECTOR2 texcoord;
};


struct StrandVertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 tangent;
    D3DXVECTOR4 texcoord;
};

struct DynamicVertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;
    D3DXVECTOR3 texmass;
    D3DXVECTOR3 velocity;
};

struct DisConstrain
{
    UINT S_ID; // strand id
    UINT V_ID1; // vert 1
    UINT V_ID2; // vert 2

    float dis; // distance between verts
    float stiffness;
};

struct AngularConstrain
{
    UINT S_ID; // strand id
    UINT V_ID_TIP; // vert tip, the one to be modified
    UINT V_ID_MID; // vert in the middle
    UINT V_ID_ROOT; // vert at root

    D3DXVECTOR3 rotAxis; // axis of rotation angle
    float angle; // angle between two segments
    float stiffness;
};
// define a 3D ellipsoid for collision constrain
// (x/a)^2 + (y/b)^2 + (z/c)^2 = 1
struct Ellipsoid
{
    D3DXVECTOR3 center;
    D3DXVECTOR3 radius;
    D3DXVECTOR3 rotate;
};

class Material
{
public:
    Material();
    ~Material();
    WCHAR   strName[MAX_PATH];

    D3DXVECTOR3 vAmbient;
    D3DXVECTOR3 vDiffuse;
    D3DXVECTOR3 vSpecular;

    int nShininess;
    float fAlpha;

    bool bSpecular;

    WCHAR   strTexture[MAX_PATH];
    IDirect3DTexture9* pTexture9; // for d3d9
    ID3D11ShaderResourceView* pTextureRV11; // for d3d 11
};
struct Subset
{
    int startIndex;
    int triangleCount;
    int materialID;
};

class Float3 {
public:
    //  Public Methods
    Float3(float _x=0, float _y=0, float _z=0)
        : x(_x), y(_y), z(_z) {	}

    Float3(D3DXVECTOR3 &v)
        : x(v.x), y(v.y), z(v.z) { }

    Float3 operator+(const Float3 &v) const {
        return Float3(x + v.x, y + v.y, z + v.z);
    }
    
    Float3& operator+=(const Float3 &v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Float3 operator-(const Float3 &v) const {
        return Float3(x - v.x, y - v.y, z - v.z);
    }
    
    Float3& operator-=(const Float3 &v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    bool operator==(const Float3 &v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    Float3 operator*(float f) const {
        return Float3(f*x, f*y, f*z);
    }
    
    Float3& operator*=(float f) {
        x *= f; y *= f; z *= f;
        return *this;
    }
    Float3 operator/(float f) const {
        Assert(f!=0, L"Denominator cannot be ZERO!");
        float inv = 1.f / f;
        return Float3(x * inv, y * inv, z * inv);
    }
    
    Float3 &operator/=(float f) {
        Assert(f!=0, L"Denominator cannot be ZERO!");
        float inv = 1.f / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    Float3 operator-() const {
        return Float3(-x, -y, -z);
    }
    float operator[](int i) const {
        Assert(i >= 0 && i <= 2, L"Array out of Bound!");
        return (&x)[i];
    }
    
    float &operator[](int i) {
        Assert(i >= 0 && i <= 2, L"Array out of Bound!");
        return (&x)[i];
    }
    float LengthSquared() const { return x*x + y*y + z*z; }
    float Length() const { return sqrtf(LengthSquared()); }
    // Vector Public Data
public:
    float x, y, z;
};

class Ray 
{
public:
    // Ray Public Methods
    Ray(): mint(RAY_EPSILON), maxt(INFINITY), time(0.f) {}
    Ray(const Float3 &origin, const Float3 &direction,
        float start = RAY_EPSILON, float end = INFINITY, float t = 0.f)
        : o(origin), d(direction), mint(start), maxt(end), time(t) { }
    Float3 operator()(float t) const { return o + d * t; }
    // Ray Public Data
    Float3 o;
    Float3 d;
    mutable float mint, maxt;
    float time;
};


class BBox 
{
public:
    // BBox Public Methods
    BBox() 
    {
        pMin = Float3( INFINITY,  INFINITY,  INFINITY);
        pMax = Float3(-INFINITY, -INFINITY, -INFINITY);
    }
    BBox(const Float3 &p) : pMin(p), pMax(p) { }
    BBox(const Float3 &p1, const Float3 &p2) 
    {
        pMin = Float3(min(p1.x, p2.x),
                     min(p1.y, p2.y),
                     min(p1.z, p2.z));
        pMax = Float3(max(p1.x, p2.x),
                     max(p1.y, p2.y),
                     max(p1.z, p2.z));
    }
    
    bool Overlaps(const BBox &b) const 
    {
        bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
        bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
        bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
        return (x && y && z);
    }
    bool Inside(const Float3 &pt) const 
    {
        return (pt.x >= pMin.x && pt.x <= pMax.x &&
                pt.y >= pMin.y && pt.y <= pMax.y &&
                pt.z >= pMin.z && pt.z <= pMax.z);
    }
    void Expand(float delta) 
    {
        pMin -= Float3(delta, delta, delta);
        pMax += Float3(delta, delta, delta);
    }
    float Volume() const {
        Float3 d = pMax - pMin;
        return d.x * d.y * d.z;
    }
    int MaximumExtent() const {
        Float3 diag = pMax - pMin;
        if (diag.x > diag.y && diag.x > diag.z)
            return 0;
        else if (diag.y > diag.z)
            return 1;
        else
            return 2;
    }
    void BoundingSphere(Float3 *c, float *rad) const;
    // BBox Public Data
public:
    Float3 pMin, pMax;
};
class BSphere
{
public:
    D3DXVECTOR3 center;
    float radius;
    BSphere()
    {
        center = D3DXVECTOR3(0,0,0);
        radius = 0;
    }
    
};

class MemoryArena 
{
private:
    // MemoryArena Private Data
    u_int curBlockPos, blockSize;
    char *currentBlock;
    vector<char*> usedBlocks, availableBlocks;

public:
    // MemoryArena Public Methods
    MemoryArena(u_int bs = 32768) 
    {
        blockSize = bs;
        curBlockPos = 0;
        currentBlock = (char *)AllocAligned(blockSize);
    }

    ~MemoryArena() 
    {
        FreeAligned(currentBlock);
        for (u_int i = 0; i < usedBlocks.size(); ++i)
            FreeAligned(usedBlocks[i]);
        for (u_int i = 0; i < availableBlocks.size(); ++i)
            FreeAligned(availableBlocks[i]);
    }
    
    void *Alloc(u_int sz) 
    {
        // Round up _sz_ to minimum machine alignment
        sz = ((sz + 7) & (~7));
        if (curBlockPos + sz > blockSize) 
        {
            // Get new block of memory for _MemoryArena_
            usedBlocks.push_back(currentBlock);
            if (availableBlocks.size() && sz <= blockSize) 
            {
                currentBlock = availableBlocks.back();
                availableBlocks.pop_back();
            }
            else
                currentBlock = (char *)AllocAligned(max(sz, blockSize));
            curBlockPos = 0;
        }
        void *ret = currentBlock + curBlockPos;
        curBlockPos += sz;
        return ret;
    }
    void FreeAll() 
    {
        curBlockPos = 0;
        while (usedBlocks.size()) 
        {
            availableBlocks.push_back(usedBlocks.back());
            usedBlocks.pop_back();
        }
    }
};

class Matrix4x4 
{
public:
    // Matrix4x4 Public Methods
    Matrix4x4() 
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (i == j) m[i][j] = 1.;
                else m[i][j] = 0.;
    }
    Matrix4x4(float mat[4][4]);
    Matrix4x4(float t00, float t01, float t02, float t03,
              float t10, float t11, float t12, float t13,
              float t20, float t21, float t22, float t23,
              float t30, float t31, float t32, float t33);
    
    void Print(ostream &os) const 
    {
        os << "[ ";
        for (int i = 0; i < 4; ++i) 
        {
            os << "[ ";
            for (int j = 0; j < 4; ++j)  
            {
                os << m[i][j];
                if (j != 3) os << ", ";
            }
            os << " ] ";
        }
        os << " ] ";
    }

    Matrix4x4 operator*(const Matrix4x4 &mat) const 
    {
        float  r[4][4];
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r[i][j] = m[i][0] * mat.m[0][j] +
                          m[i][1] * mat.m[1][j] +
                          m[i][2] * mat.m[2][j] +
                          m[i][3] * mat.m[3][j];

        return Matrix4x4(r);
    }
    Matrix4x4* Transpose() const
    {
       return new Matrix4x4(m[0][0], m[1][0], m[2][0], m[3][0],
                            m[0][1], m[1][1], m[2][1], m[3][1],
                            m[0][2], m[1][2], m[2][2], m[3][2],
                            m[0][3], m[1][3], m[2][3], m[3][3]);
    }
    Matrix4x4* Inverse(Matrix4x4 &dest) const
    {
        int indxc[4], indxr[4];
        int ipiv[4] = { 0, 0, 0, 0 };
        float minv[4][4];
        memcpy(minv, m, 4*4*sizeof(float));
        for (int i = 0; i < 4; i++) 
        {
            int irow = -1, icol = -1;
            float big = 0.;
            // Choose pivot
            for (int j = 0; j < 4; j++) 
            {
                if (ipiv[j] != 1) 
                {
                    for (int k = 0; k < 4; k++) 
                    {
                        if (ipiv[k] == 0) 
                        {
                            if (fabsf(minv[j][k]) >= big) 
                            {
                                big = float(fabsf(minv[j][k]));
                                irow = j;
                                icol = k;
                            }
                        }
                        else Assert(ipiv[k] <= 1, L"Singular matrix in MatrixInvert");
                    }
                }
            }
            ++ipiv[icol];
            // Swap rows _irow_ and _icol_ for pivot
            if (irow != icol) 
            {
                for (int k = 0; k < 4; ++k)
                    swap(minv[irow][k], minv[icol][k]);
            }
            indxr[i] = irow;
            indxc[i] = icol;
            Assert(minv[icol][icol] != 0., L"Singular matrix in MatrixInvert");
            
            // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
            float pivinv = 1.f / minv[icol][icol];
            minv[icol][icol] = 1.f;
            for (int j = 0; j < 4; j++)
                minv[icol][j] *= pivinv;
            // Subtract this row from others to zero out their columns
            for (int j = 0; j < 4; j++) 
            {
                if (j != icol) 
                {
                    float save = minv[j][icol];
                    minv[j][icol] = 0;
                    for (int k = 0; k < 4; k++)
                        minv[j][k] -= minv[icol][k]*save;
                }
            }
        }
        // Swap columns to reflect permutation
        for (int j = 3; j >= 0; j--) 
        {
            if (indxr[j] != indxc[j]) 
            {
                for (int k = 0; k < 4; k++)
                    swap(minv[k][indxr[j]], minv[k][indxc[j]]);
            }
        }
        return new Matrix4x4(minv);
    }
public:
    float m[4][4];
};
BBox Union(const BBox &b, const Float3 &p);
BBox Union(const BBox &b, const BBox &b2);

inline Float3 Normalize(const Float3 &v);
inline float Distance(const Float3 &p1, const Float3 &p2);
inline Float3 Cross(const Float3 &v1, const Float3 &v2);
inline float Dot(const Float3 &v1, const Float3 &v2);

Float3 TransformPoint(const Matrix4x4 &m, const Float3 &pt);
