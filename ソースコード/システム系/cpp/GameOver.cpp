//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : 
//
//=============================================================================
#include "stdlib.h"
#include "GameOver.h"
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	gameoverTex = 0;	// �e�N�X�`�����
static int	continueTex = 0;
static int	selectstageTex = 0;
static int	exitTex = 0;

static int SE_gameover1;
static int SE_gameover2;

static int waku = 0;
int o = 1;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameOver(void)
{

	SE_gameover1 = LoadSound("data/SE/�J�[�\���ړ�1.wav");
	SetVolume(SE_gameover1, 0.4f);
	SE_gameover2 = LoadSound("data/SE/����A�{�^������13.wav");
	SetVolume(SE_gameover2, 0.4f);

	gameoverTex = LoadTexture("data/TEXTURE/game_over.png");
	continueTex = LoadTexture("data/TEXTURE/game_over_retry .png");
	selectstageTex = LoadTexture("data/TEXTURE/game_over_select.png");
	exitTex = LoadTexture("data/TEXTURE/game_over_retire.png");

	waku = LoadTexture("data/TEXTURE/kiiro_touka.png");
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameOver(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================

void UpdateGameOver(void)
{

	if (GetFadeState() == FADE_NONE)
	{
		bool pushed = false;

		if (GetKeyboardTrigger(DIK_RETURN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			StopSoundAll();
			PlaySound(SE_gameover2, false);
			switch (GetSceneState())
			{
			case SCENE_GAMEOVER_cont:
				o = 1;
				SceneTransition(GetSceneOld());

				break;
			case SCENE_GAMEOVER_selec:
				o = 1;
				PlaySoundOnTitle();
				SceneTransition(SCENE_WORLD1);
				break;
			case SCENE_GAMEOVER_exit:
				o = 1;
				GAMEEND();
				break;
			}
		}

		if (GetKeyboardTrigger(DIK_RIGHT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			o += 1;
			pushed = true;
		}

		if (GetKeyboardTrigger(DIK_LEFT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			o -= 1;
			pushed = true;
		}

		//����ȏ�s���Ȃ�
		if (o < 1)
		{
			o = 1;
			pushed = false;
		}

		if (o > 3)
		{
			o = 3;
			pushed = false;
		}


		if (pushed)
		{
			PlaySound(SE_gameover1, false);
			switch (o)
			{
			case 1:

				SceneTransition(SCENE_GAMEOVER_cont);
				break;

			case 2:

				SceneTransition(SCENE_GAMEOVER_selec);
				break;
			case 3:

				SceneTransition(SCENE_GAMEOVER_exit);
				break;
			}
			UpdateGameOver();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameOver_cont(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(gameoverTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(continueTex, 100.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(selectstageTex, 520.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitTex, 940.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(waku, 114.0f, 525.0f, 220, 105, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawGameOver_selec(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(gameoverTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(continueTex, 100.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(selectstageTex, 520.0f, 450.0f, 250, 250, 1.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitTex, 940.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(waku, 535.0f, 525.0f, 220, 105, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawGameOver_exit(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(gameoverTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(continueTex, 100.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(selectstageTex, 520.0f, 450.0f, 250, 250, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitTex, 940.0f, 450.0f, 250, 250, 1.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteLeftTop(waku, 955.0f, 525.0f, 220, 105, 0.0f, 0.0f, 1.0f, 1.0f);
}