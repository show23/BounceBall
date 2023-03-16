//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "world_choice.h"
#include "stage_choice.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "fade.h"
#include "scene.h"
#include "sound.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	world1Tex = 0;	// �e�N�X�`�����
static int	world2Tex = 0;
static int	world3Tex = 0;
static int  exitWorldTex = 0;

static int	BackTex = 0;
static int  FrameTex = 0;
static int	g_BGMNo = 0;		// BGM���ʎq
int n = 1;

unsigned static int SE_worldchoice1;//���̂ق�
unsigned static int SE_worldchoice2;//����̂ق�

static int	BGM_WorldSelect;		// BGM���ʎq

//=============================================================================
// ����������
//=============================================================================

HRESULT InitWorld(void)
{

	SE_worldchoice1 = LoadSound("data/SE/�J�[�\���ړ�1.wav");
	SetVolume(SE_worldchoice1, 0.4f);
	SE_worldchoice2 = LoadSound("data/SE/����A�{�^������13.wav");
	SetVolume(SE_worldchoice2, 0.4f);


	//�e�N�X�`������
	world1Tex = LoadTexture("data/TEXTURE/1.png");
	world2Tex = LoadTexture("data/TEXTURE/2.png");
	world3Tex = LoadTexture("data/TEXTURE/3.png");
	BackTex = LoadTexture("data/TEXTURE/MAP Select.png");
	exitWorldTex = LoadTexture("data/TEXTURE/game_over_retire.png");
	
	FrameTex = LoadTexture("data/TEXTURE/kiiro_touka.png");



	switch (GetSceneState())
	{
	case SCENE_WORLD1:
		n = 1;
		break;
	case SCENE_WORLD2:
		n = 2;
		break;
	case SCENE_WORLD3:
		n = 3;
		break;
	case SCENE_WORLD4:
		n = 4;
		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorld(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================



void UpdateWorld(void)
{
	if (GetFadeState() == FADE_NONE)
	{

		bool pushed = false;

		if (GetKeyboardTrigger(DIK_BACK) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			SceneTransition(SCENE_TITLE);
		}
		//�E
		if (GetKeyboardTrigger(DIK_RIGHT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{

			pushed = true;
			n += 1;
		}

		//��
		if (GetKeyboardTrigger(DIK_LEFT) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			pushed = true;
			n -= 1;
		}

		if (GetKeyboardTrigger(DIK_UP) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			if (n > 2) {
				pushed = true;
				n -= 2;
			}
		}

		if (GetKeyboardTrigger(DIK_DOWN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			if (n <= 2) {
				pushed = true;
				n += 2;
			}
		}


		if (GetKeyboardTrigger(DIK_RETURN) || GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{

			PlaySound(SE_worldchoice2, false);
			switch (n)
			{
			case 1:
				SceneTransition(SCENE_STAGE1_1);
				break;
			
			case 2:
				SceneTransition(SCENE_STAGE2_1);
				break;
			
			case 3:
				SceneTransition(SCENE_STAGE3_1);
				break;
			case 4:
				GAMEEND();
				break;
			}

		}

		//����ȏ�s���Ȃ�
		if (n < 1)
		{
			n = 1;
			pushed = false;
		}
		if (n > 4)
		{
			n = 4;
			pushed = false;
		}

		if (pushed)
		{
			PlaySound(SE_worldchoice1, false);
			switch (n)
			{
			case 1:
				SceneTransition(SCENE_WORLD1);
				break;

			case 2:
				SceneTransition(SCENE_WORLD2);
				break;

			case 3:
				SceneTransition(SCENE_WORLD3);
				break;
			case 4:
				SceneTransition(SCENE_WORLD4);
				break;
			}


			
			UpdateWorld();
		}
	}
	

	
}

//=============================================================================
// �`�揈��
//============================================================================
void DrawWorld1(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitWorldTex, 670.0f, 190.0f, 460, 460, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(FrameTex, 150.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world2Tex, 850.0f, 100.0f, 100,100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world3Tex, 300.0f, 380.0f, 100,100, 0.0f, 0.0f, 1.0f, 1.0f);

}

void DrawWorld2(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitWorldTex, 670.0f, 190.0f, 460, 460, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(FrameTex, 690.0f, 50.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawWorld3(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitWorldTex, 670.0f, 190.0f, 460, 460, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(FrameTex, 150.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}

void DrawWorld4(void)
{
	DrawSpriteLeftTop(BackTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(exitWorldTex, 678.0f, 199.0f, 450, 440, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(FrameTex, 690.0f, 320.0f, 425, 205, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world1Tex, 300.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world2Tex, 850.0f, 100.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(world3Tex, 300.0f, 380.0f, 100, 100, 0.0f, 0.0f, 1.0f, 1.0f);
}