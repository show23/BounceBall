//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
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
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	title_BGTex = 0;	// �e�N�X�`�����
static int	titleTex = 0;

static int	StartTex = 0;


int g_timer = 0;
int alfa = 1;
unsigned static int	BGM_title;		// BGM���ʎq
unsigned static int	SE_title;		// BGM���ʎq

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	StopSoundAll();
	int alfa = 1;
	titleTex = LoadTexture("data/TEXTURE/Title.png");
	//�e�N�X�`������
	title_BGTex = LoadTexture("data/TEXTURE/BG_title.png");


	StartTex = LoadTexture("data/TEXTURE/Push_to_start.png"); 

	BGM_title = LoadSound("data/BGM/Reflex_Reduction.wav");
	SetVolume(BGM_title, 0.2f);


	SE_title = LoadSound("data/SE/����A�{�^������13.wav");
	SetVolume(SE_title, 0.4f);
	PlaySound(BGM_title, -1);
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
}

//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(title_BGTex, 0.0f, 0.0f, 6288, 750, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(titleTex, 50.0f, -50.0f, 1200, 800, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteColor(StartTex, 650.0f, 450.0f, 400, 50, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, alfa));
}

void PlaySoundOnTitle() {

	PlaySound(BGM_title, -1);
	SetVolume(BGM_title, 0.05f);
}

