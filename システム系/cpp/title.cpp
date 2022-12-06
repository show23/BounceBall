//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"

#include "sound.h"

#include "fade.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	title_BGTex = 0;	// テクスチャ情報
static int	titleTex = 0;

static int	StartTex = 0;


int g_timer = 0;
int alfa = 1;
unsigned static int	BGM_title;		// BGM識別子
unsigned static int	SE_title;		// BGM識別子

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	StopSoundAll();
	int alfa = 1;
	titleTex = LoadTexture("data/TEXTURE/Title.png");
	//テクスチャ生成
	title_BGTex = LoadTexture("data/TEXTURE/BG_title.png");


	StartTex = LoadTexture("data/TEXTURE/Push_to_start.png"); 

	BGM_title = LoadSound("data/BGM/Reflex_Reduction.wav");
	SetVolume(BGM_title, 0.2f);


	SE_title = LoadSound("data/SE/決定、ボタン押下13.wav");
	SetVolume(SE_title, 0.4f);
	PlaySound(BGM_title, -1);
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	if ((GetKeyboardTrigger(DIK_RETURN) ||  GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B) && GetFadeState() == FADE_NONE)
	{
		//SceneTransition(SCENE_GAME);
		PlaySound(SE_title, false);
		SetVolume(BGM_title, 0.05f);
		SceneTransition(SCENE_WORLD1);
	}

	//kakusi
	if (((GetKeyboardPress(DIK_BACK) && GetKeyboardPress(DIK_SPACE)) ||
		(GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_A && GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_X&& GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_Y)) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_PLAN_SECRET);
	}
	//g_timer++;
	//if (g_timer > 50) {
	//	g_timer = 50;
	//	alfa = 0;
	//}
	//
	


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(title_BGTex, 0.0f, 0.0f, 6288, 750, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(titleTex, 50.0f, -50.0f, 1200, 800, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteColor(StartTex, 650.0f, 450.0f, 400, 50, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, alfa));
}

void PlaySoundOnTitle() {

	PlaySound(BGM_title, -1);
	SetVolume(BGM_title, 0.05f);
}

