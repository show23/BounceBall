//=============================================================================
//
// clear
// Author : 
//
//=============================================================================
#include "stdlib.h"
#include "clear.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "scene.h"
#include "main.h"
#include "timer.h"
#include "score.h"
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
static int  WakuTex = 0;
static int  IdleTex = 0;
static int  ConceptTex = 0;

static int SE_clear1;
static int SE_clear2;

int g_ResultTime = 0;
int g_ResultTime1 = 0;
int p = 1;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitClear(void)
{
	BackTex = LoadTexture("data/TEXTURE/Result.png");
	WakuTex = LoadTexture("data/TEXTURE/kiiro_touka.png");
	IdleTex = LoadTexture("data/TEXTURE/IdleResult.png");
	ConceptTex = LoadTexture("data/TEXTURE/ClearBack.png");

	SE_clear1 = LoadSound("data/SE/カーソル移動1.wav");
	SetVolume(SE_clear1, 0.4f);
	SE_clear2 = LoadSound("data/SE/決定、ボタン押下13.wav");
	SetVolume(SE_clear2, 0.4f);

	switch (GetSceneState())
	{
	case SCENE_CLEAR_cont:
		p = 1;
		break;
	case SCENE_CLEAR_selec:
		p = 2;
		break;
	case SCENE_CLEAR_next:
		p = 3;
		break;
	case SCENE_CLEAR_exit:
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitClear(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================

void UpdateClear(void)
{


	if (GetFadeState() == FADE_NONE)
	{
		bool pushed = false;
		if (GetKeyboardTrigger(DIK_RETURN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			StopSoundAll();
			PlaySound(SE_clear2, false);
			switch (GetSceneState())
			{
			case SCENE_CLEAR_cont:
				p = 1;
				SceneTransition(GetSceneOld());
				break;
			case SCENE_CLEAR_selec:
				p = 1;
				PlaySoundOnTitle();
				SceneTransition(SCENE_WORLD1);
				break;
			case SCENE_CLEAR_next:
				p = 1;
				nextScene();
				break;
			case SCENE_CLEAR_exit:
				GAMEEND();
				break;
			}
		}

		if (GetKeyboardTrigger(DIK_RIGHT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			p += 1;
			pushed = true;
		}

		if (GetKeyboardTrigger(DIK_LEFT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			p -= 1;
			pushed = true;
		}

		//これ以上行くなよ
		if (p < 1)
		{
			p = 1;
			pushed = false;
		}

		if (p > 4)
		{
			p = 4;
			pushed = false;
		}


		if (pushed)
		{
			PlaySound(SE_clear1, false);
			switch (p)
			{
			case 1:
				SceneTransition(SCENE_CLEAR_cont);
				break;

			case 2:
				SceneTransition(SCENE_CLEAR_selec);
				break;
			case 3:
				SceneTransition(SCENE_CLEAR_next);
				break;
			case 4:
				SceneTransition(SCENE_CLEAR_exit);
				break;
			}
			UpdateClear();
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawClear_cont(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(ConceptTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(WakuTex, 144, 505, 290, 135, 0.0f, 0.0f, 1.0f, 1.0f);
	Result();
}

void DrawClear_selec(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(ConceptTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(WakuTex, 435, 505, 350, 135, 0.0f, 0.0f, 1.0f, 1.0f);
	Result();
}

void DrawClear_next(void)
{
	DrawSpriteLeftTop(ConceptTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(WakuTex, 800, 505, 200, 135, 0.0f, 0.0f, 1.0f, 1.0f);
	Result();
}
void DrawClear_exit(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(ConceptTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(WakuTex, 1000, 505, 233, 135, 0.0f, 0.0f, 1.0f, 1.0f);
	Result();
}

void nextScene(void)
{
	StopSoundAll();
	switch (GetSceneOld())
	{
	case SCENE_GAME1_1:
		SceneTransition(SCENE_GAME1_2);
		break;
	case SCENE_GAME1_2:
		SceneTransition(SCENE_GAME1_3);
		break;
	case SCENE_GAME1_3:
		SceneTransition(SCENE_GAME1_4);
		break;
	case SCENE_GAME1_4:
		SceneTransition(SCENE_GAME2_1);
		break;
	case SCENE_GAME2_1:
		SceneTransition(SCENE_GAME2_2);
		break;
	case SCENE_GAME2_2:
		SceneTransition(SCENE_GAME2_3);
		break;
	case SCENE_GAME2_3:
		SceneTransition(SCENE_GAME2_4);
		break;
	case SCENE_GAME2_4:
		SceneTransition(SCENE_GAME3_1);
		break;
	case SCENE_GAME3_1:
		SceneTransition(SCENE_GAME3_2);
		break;
	case SCENE_GAME3_2:
		SceneTransition(SCENE_GAME3_3);
		break;
	case SCENE_GAME3_3:
		SceneTransition(SCENE_GAME3_4);
		break;
	case SCENE_GAME3_4:
		SceneTransition(SCENE_TITLE);
		break;
	}
}

void Result()
{
	getOldTime();
	OldScore();
	Evaluation();
}


void Evaluation(void)
{
	switch (GetSceneOld())
	{
	case SCENE_GAME1_1:
		SetOldTime(70, 65, 50,  0);//左からSABC
		SetOldScore(580, 460, 330, 0);//左からSABC
		break;

	case SCENE_GAME1_2:
		SetOldTime(64, 56, 45, 0);//左からSABC
		SetOldScore(590, 480, 390, 0);//左からSABC
		break;

	case SCENE_GAME1_3:
		SetOldTime(46, 31, 22, 0);//左からSABC
		SetOldScore(640, 580, 420, 0);//左からSABC
		break;

	case SCENE_GAME1_4:
		SetOldTime(63, 52, 41, 0);//左からSABC
		SetOldScore(700, 620, 510, 0);//左からSABC
		break;

	case SCENE_GAME2_1:
		SetOldTime(45, 33, 19, 0);//左からSABC
		SetOldScore(990, 750, 600, 0);//左からSABC
		break;

	case SCENE_GAME2_2:
		SetOldTime(58, 48, 32, 0);//左からSABC
		SetOldScore(460, 320, 220, 0);//左からSABC
		break;

	case SCENE_GAME2_3:
		SetOldTime(42, 30, 20, 0);//左からSABC
		SetOldScore(360, 280, 170, 0);//左からSABC
		break;

	case SCENE_GAME2_4:
		SetOldTime(70, 62, 50, 0);//左からSABC
		SetOldScore(550, 420, 320, 0);//左からSABC
		break;

	case SCENE_GAME3_1:
		SetOldTime(43, 31, 20, 0);//左からSABC
		SetOldScore(490, 380, 250, 0);//左からSABC
		break;

	case SCENE_GAME3_2:
		SetOldTime(85, 77, 65, 0);//左からSABC
		SetOldScore(590, 480, 380, 0);//左からSABC
		break;

	case SCENE_GAME3_3:
		SetOldTime(65, 55, 42, 0);//左からSABC
		SetOldScore(490, 380, 280, 0);//左からSABC
		break;

	case SCENE_GAME3_4:
		SetOldTime(63, 51, 40, 0);//左からSABC
		SetOldScore(800, 720, 500, 0);//左からSABC
		break;
	}
}