//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "stdlib.h"
#include "secret.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "scene.h"
#include "main.h"
#include "game.h"
#include "sound.h"
#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	BackTex = 0;
static int	BackDesiTex = 0;
static int	BackProgrTex = 0;
static int	BackPlanTex = 0;

static int	programmerTex = 0;	// テクスチャ情報
static int	plannerTex = 0;
static int	designerTex = 0;




static int	haradaTex = 0;
static int	oosimaTex = 0;
static int	okadaTex = 0;
static int	hukudaTex = 0;
static int	inTex = 0;
static int	ruwanTex = 0;
static int	iiyosiTex = 0;

static int	raTex = 0;

static int SE_gameover1;
static int SE_gameover2;

static int waku = 0;
int g_timesecrect = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSecret(void)
{


	//SE_gameover1 = LoadSound("data/SE/カーソル移動1.wav");
	//SetVolume(SE_gameover1, 0.4f);
	//SE_gameover2 = LoadSound("data/SE/決定、ボタン押下13.wav");
	//SetVolume(SE_gameover2, 0.4f);
	BackTex = LoadTexture("data/TEXTURE/Back.png");
	BackDesiTex = LoadTexture("data/TEXTURE/concept.png");
	BackProgrTex = LoadTexture("data/TEXTURE/propglam.png");
	BackPlanTex = LoadTexture("data/TEXTURE/Backplanner.png");

	programmerTex = LoadTexture("data/TEXTURE/programmer1.png");
	plannerTex = LoadTexture("data/TEXTURE/planner1.png");
	designerTex = LoadTexture("data/TEXTURE/designer1.png");
	


	haradaTex = LoadTexture("data/TEXTURE/harada1.png");
	oosimaTex = LoadTexture("data/TEXTURE/oosima1.png");
	okadaTex = LoadTexture("data/TEXTURE/okada1.png");
	hukudaTex = LoadTexture("data/TEXTURE/hukuda1.png");
	inTex = LoadTexture("data/TEXTURE/in1.png");
	ruwanTex = LoadTexture("data/TEXTURE/ruwan1.png");
	iiyosiTex = LoadTexture("data/TEXTURE/iiyosi1.png");
	raTex = LoadTexture("data/TEXTURE/ra1.png");


	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSecret(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================

void UpdateSecret(void)
{
	
	g_timesecrect++;
	if (g_timesecrect > 200) {
		g_timesecrect = 0;
		if(GetSceneState() == SCENE_PLAN_SECRET)
		    SceneTransition(SCENE_PROG_SECRET);

		else if(GetSceneState() == SCENE_PROG_SECRET)
			SceneTransition(SCENE_DESI_SECRET);

		else
			SceneTransition(SCENE_TITLE);
	}
	
}

void DrawPlannerSecret(void)
{
	
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteColor(BackPlanTex, 640.0f, 360.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0, 0.2));
	DrawSpriteLeftTop(plannerTex, 350.0f, 10.0f,  600, 200, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(haradaTex,  400.0f, 250.0f, 450, 150, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(raTex,      400.0f, 500.0f, 400, 150, 0.0f, 0.0f, 1.0f, 1.0f);

}

void DrawProgrammerSecret(void)
{
	
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteColor(BackProgrTex, 640.0f, 360.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0, 0.3));
	DrawSpriteLeftTop(programmerTex, 440.0f, 10.0f, 500, 200, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(oosimaTex, 450.0f, 200.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(okadaTex,  450.0f, 370.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(hukudaTex, 450.0f, 540.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawDesignerSecret(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteColor(BackDesiTex, 640.0f, 360.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0,0.3));
	DrawSpriteLeftTop(designerTex, 450.0f, 10.0f, 400, 200, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(inTex,       450.0f, 200.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(ruwanTex,    450.0f, 370.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(iiyosiTex,   450.0f, 540.0f, 400, 120, 0.0f, 0.0f, 1.0f, 1.0f);
}
