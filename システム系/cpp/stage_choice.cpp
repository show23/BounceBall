//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "world_choice.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include"stage_choice.h"
#include "fade.h"
#include "scene.h"
#include "sound.h"
#include "game.h"

//----------------------------------------------
//ステージ系のスクリプトのヘッダー
//----------------------------------------------
#include"stage_choice.h"
#include "TEST_SCENE.h"

#include "SCENE_1_1.h"
#include "SCENE_1_2.h"
#include "SCENE_1_3.h"
#include "SCENE_1_4.h"


#include "SCENE_2_1.h"
#include "SCENE_2_2.h"
#include "SCENE_2_3.h"
#include "SCENE_2_4.h"

#include "SCENE_3_1.h"
#include "SCENE_3_2.h"
#include "SCENE_3_3.h"
#include "SCENE_3_4.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	stage1Tex = 0;	// テクスチャ情報
static int	stage2Tex = 0;
static int	stage3Tex = 0;
static int  stage4Tex = 0;

static int	BackTex = 0;
static int  FrameTex = 0;


STAGECHOICE stagechoice;

unsigned static int SE_stagechoice1;//矢印のほう
unsigned static int SE_stagechoice2;//決定のほう

static int	BGM_StageSelect;		// BGM識別子

int m = 1;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage(void)
{
	SE_stagechoice1 = LoadSound("data/SE/カーソル移動1.wav");
	SetVolume(SE_stagechoice1, 0.4f);
	SE_stagechoice2 = LoadSound("data/SE/決定、ボタン押下13.wav");
	SetVolume(SE_stagechoice2, 0.4f);

	//テクスチャ生成
	stage1Tex = LoadTexture("data/TEXTURE/1.png");
	stage2Tex = LoadTexture("data/TEXTURE/2.png");
	stage3Tex = LoadTexture("data/TEXTURE/3.png");
	stage4Tex = LoadTexture("data/TEXTURE/4.png");
	BackTex = LoadTexture("data/TEXTURE/Stage_Select.png");

	FrameTex = LoadTexture("data/TEXTURE/kiiro_touka.png");


	switch (GetSceneState())
	{
	case SCENE_STAGE1_1:
		m = 1;
		break;
	case SCENE_STAGE1_2:
		m = 2;
		break;
	case SCENE_STAGE1_3:
		m = 3;
		break;
	case SCENE_STAGE1_4:
		m = 4;
		break;
	case SCENE_STAGE2_1:
		m = 1;
		break;
	case SCENE_STAGE2_2:
		m = 2;
		break;
	case SCENE_STAGE2_3:
		m = 3;
		break;
	case SCENE_STAGE2_4:
		m = 4;
		break;
	case SCENE_STAGE3_1:
		m = 1;
		break;
	case SCENE_STAGE3_2:
		m = 2;
		break;
	case SCENE_STAGE3_3:
		m = 3;
		break;
	case SCENE_STAGE3_4:
		m = 4;
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================

void UpdateStage(void)
{
	if (GetFadeState() == FADE_NONE)
	{
		bool pushed = false;
		
		if (GetKeyboardTrigger(DIK_BACK) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			SceneTransition(SCENE_WORLD1);
		}

		if (GetKeyboardTrigger(DIK_RIGHT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			pushed = true;
			m += 1;
		}

		if (GetKeyboardTrigger(DIK_LEFT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			pushed = true;
			m -= 1;
		}

		if (GetKeyboardTrigger(DIK_UP) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			if(m > 2){
			pushed = true;
			m -= 2;
			}
		}

		if (GetKeyboardTrigger(DIK_DOWN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			if (m <= 2) {
				pushed = true;
				m += 2;
			}
		}

		//これ以上行くなよ
		if (m < 1)
		{
			m = 1;
			pushed = false;
		}
		if (m > 4)
		{
			m = 4;
			pushed = false;
		}

		if (pushed)
		{
			PlaySound(SE_stagechoice1, false);
			if (GetSceneState() == SCENE_STAGE1_1 || GetSceneState() == SCENE_STAGE1_2 || GetSceneState() == SCENE_STAGE1_3 || GetSceneState() == SCENE_STAGE1_4)
			{
				switch (m)
				{
				case 1:
					SceneTransition(SCENE_STAGE1_1);
					break;
				case 2:
					SceneTransition(SCENE_STAGE1_2);
					break;
				case 3:
					SceneTransition(SCENE_STAGE1_3);
					break;
				case 4:
					SceneTransition(SCENE_STAGE1_4);
					break;
				}

			}

			if (GetSceneState() == SCENE_STAGE2_1 || GetSceneState() == SCENE_STAGE2_2 || GetSceneState() == SCENE_STAGE2_3 || GetSceneState() == SCENE_STAGE2_4)
			{
				switch (m)
				{
				case 1:
					SceneTransition(SCENE_STAGE2_1);
					break;
				case 2:
					SceneTransition(SCENE_STAGE2_2);
					break;
				case 3:
					SceneTransition(SCENE_STAGE2_3);
					break;
				case 4:
					SceneTransition(SCENE_STAGE2_4);
					break;
				}

			}


			if (GetSceneState() == SCENE_STAGE3_1 || GetSceneState() == SCENE_STAGE3_2 || GetSceneState() == SCENE_STAGE3_3 || GetSceneState() == SCENE_STAGE3_4)
			{
				switch (m)
				{
				case 1:
					SceneTransition(SCENE_STAGE3_1);
					break;
				case 2:
					SceneTransition(SCENE_STAGE3_2);
					break;
				case 3:
					SceneTransition(SCENE_STAGE3_3);
					break;
				case 4:
					SceneTransition(SCENE_STAGE3_4);
					break;
				}

			}

			UpdateStage();
		}

	}

	if (GetKeyboardTrigger(DIK_RETURN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		PlaySound(SE_stagechoice2, false);
		switch (GetSceneState())
		{
		case SCENE_STAGE1_1:
			SceneTransition(SCENE_GAME1_1);
			break;
		case SCENE_STAGE1_2:
			SceneTransition(SCENE_GAME1_2);
			break;
		case SCENE_STAGE1_3:
			SceneTransition(SCENE_GAME1_3);
			break;
		case SCENE_STAGE1_4:
			SceneTransition(SCENE_GAME1_4);
			break;

		case SCENE_STAGE2_1:
			SceneTransition(SCENE_GAME2_1);
			break;
		case SCENE_STAGE2_2:
			SceneTransition(SCENE_GAME2_2);
			break;
		case SCENE_STAGE2_3:
			SceneTransition(SCENE_GAME2_3);
			break;
		case SCENE_STAGE2_4:
			SceneTransition(SCENE_GAME2_4);
			break;

		case SCENE_STAGE3_1:
			SceneTransition(SCENE_GAME3_1);
			break;
		case SCENE_STAGE3_2:
			SceneTransition(SCENE_GAME3_2);
			break;
		case SCENE_STAGE3_3:
			SceneTransition(SCENE_GAME3_3);
			break;
		case SCENE_STAGE3_4:
			SceneTransition(SCENE_GAME3_4);
			break;
		}



	}
	

}



//=============================================================================
// 描画処理
//=============================================================================

void DrawStage1_1(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 150.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}


void DrawStage1_2(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawStage1_3(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 150.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage1_4(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}


void DrawStage2_1(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	
	DrawSpriteLeftTop(FrameTex, 150.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage2_2(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage2_3(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 150.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage2_4(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}



void DrawStage3_1(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 150.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawStage3_2(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage3_3(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 150.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}
void DrawStage3_4(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(FrameTex, 690.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(stage1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stage4Tex, 850.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}


