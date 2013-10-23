//--------------------------------------------------------------------------------------
// File: SceneParams.h
//
// Global configuration parameters for rendering
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

extern int g_ScreenWidth;
extern int g_ScreenHeight;

#define SM_SCENE_WIDTH	640
#define SM_SCENE_HEIGHT	640

#define SM_HAIR_WIDTH	640
#define SM_HAIR_HEIGHT	640

const static UINT			g_HairTotalLayers = 8; 

// light color
static const D3DXVECTOR3	g_vPointLight = D3DXVECTOR3(1.f, 1.f, 1.f);
static const D3DXVECTOR3	g_vAmbientLight = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

const D3DXVECTOR3			g_vLightPosition = D3DXVECTOR3(421.25043f, 306.7890949f, 343.22232f);
const D3DXVECTOR3			g_vLightAt = D3DXVECTOR3(0.f, 0.f, 0.f);

const D3DXVECTOR3			g_vCameraPosition = D3DXVECTOR3(190.0f, 70.0f, 250.0f);
const D3DXVECTOR3			g_vCameraAt = D3DXVECTOR3(0, 40, 0);

const D3DXVECTOR3			g_vTranslation = D3DXVECTOR3(0.f, 0.f, 0.f);
const D3DXVECTOR3			g_vRotation = D3DXVECTOR3(0.f, 0.f, 0.f);
const float					g_fScale = 1.f;

static const D3DXVECTOR3	g_vHairKa = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
static const D3DXVECTOR3	g_vHairKd = D3DXVECTOR3(0.4f, 0.0f, 2.0f);
static const D3DXVECTOR3	g_vHairKs = D3DXVECTOR3(0.14f, 0.0f, 2.0f);
static const D3DXVECTOR3	g_vHairEx = D3DXVECTOR3(80.f, 1.f, 100.f);
static const D3DXVECTOR3	g_vHairKs2 = D3DXVECTOR3(0.5f, 0.0f, 2.0f);
static const D3DXVECTOR3	g_vHairEx2 = D3DXVECTOR3(8.f, 1.f, 100.f);

static const D3DXVECTOR3	g_vHairDensity = D3DXVECTOR3(1.f, 0.f, 1.f);

static const D3DXVECTOR3	g_vHairAlpha = D3DXVECTOR3(0.33f, 0.f, 0.99f);
static const D3DXVECTOR3	g_vHairAlphaSM = D3DXVECTOR3(0.004f, 0.f, 0.03f);

static const D3DXVECTOR3	g_vFiberRadius = D3DXVECTOR3(0.14f, 0.02f, 0.2f); // in mm
static const D3DXVECTOR3	g_vFiberSpacing = D3DXVECTOR3(0.3f, 0.1f, 2.f); // 1 fiber every 15 x fiber-radius distance

// Hair parameters
static COLORREF g_vCustHairColors[16] =
		{
			RGB( 112,  84,  48 ),	//1 brown
			RGB( 100,  68,  55 ),	//2 dark purple brown
            RGB(  59,  48,  36 ),	//3 darkest brown
            RGB(  78,  67,  63 ),	//4 Med dard brown
            RGB(  80,  68,  68 ),	//5 chestnut brown
            RGB( 106,  78,  66 ),	//6 lt chestnut brown
            RGB(  85,  72,  56 ),	//7 dark golden brown
            RGB( 167, 133, 106 ),	//8 light golden brown 
            RGB( 184, 151, 120 ),	//9 dark honey blonde
            RGB( 220, 208, 186 ),	//10 bleached blonde
            RGB( 222, 188, 153 ),	//11 light ash blonde 
            RGB( 151, 121,  97 ),	//12 med ash brown 
            RGB( 230, 206, 168 ),	//13 lightest blonde 
            RGB( 229, 200, 168 ),	//14 pale golden blonde
            RGB( 165, 107,  70 ),	//15 strawberry blonde
            RGB( 145,  85,  61 ),	//16 light aubum
//          RGB(  83,  61,  50 ),	//17 dark aubum
//          RGB( 113,  99,  90 ),	//18 daresk gray 
//          RGB( 183, 166, 158 ),	//19 med gray 
//          RGB( 214, 196, 194 ),	//20 light gray 
//          RGB( 255,  24, 225 ),	//21 white blonde 
//          RGB( 202, 191, 177 ),	//22 platinum blonde
//          RGB( 141,  74,  67 ),	//23 russet red
//          RGB( 181,  82,  57 ),	//24 terra cotta
//          RGB(  27,  27,  17 ),	//25 dark dark brown 
//          RGB(   1,   1,   1 ),	//26 black 
		};

// Hair Data Files
static const char* g_hair_top = ".\\media\\Hair\\hair_free.tfx";   
static const char* g_hair_back = ".\\media\\Hair\\hair_pulled.tfx";   
static const char* g_hair_ponytail = ".\\media\\Hair\\hair_tail.tfx";   
static const char* g_hair_front_long = ".\\media\\Hair\\hair_front_long.tfx";
