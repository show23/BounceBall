

#include "main.h"
#include "Player.h"
#include "Scroll.h"


//���[���h���W
/*
���̐��l���g���ăv���C���[����Ȃ��z��𓮂���
�w�i�Ƃ���Ƃ�
*/
static D3DXVECTOR2 g_CameraPos;
static D3DXVECTOR2 g_CameraPoint;//�J�������������Ƃ��̈ړ��ڕW

int CameraMoveFlame = 0;
bool CamMoveByScript = false;//�J�������v���C���[�̈ړ��ȊO�œ������Ƃ�true�ɂ���

static int HowFlameMove = 5; //���̎����t���[���J������h�炷��

void UpdateCamera(D3DXVECTOR2 new_pos)
{
	D3DXVECTOR2 window_half
	{
		SCREEN_WIDTH / 2.0f,
		SCREEN_HEIGHT / 2.0f
	};

	g_CameraPos = new_pos;
	// ���W�X�V
	if (CamMoveByScript) {
		g_CameraPos += g_CameraPoint;
		if (g_CameraPos.x > new_pos.x) g_CameraPoint.x += +1.0f;
		if (g_CameraPos.x < new_pos.x) g_CameraPoint.x += -1.0f;
		if (g_CameraPos.y > new_pos.y) g_CameraPoint.y += +1.0f;
		if (g_CameraPos.y < new_pos.y) g_CameraPoint.y += -1.0f;
		if (g_CameraPos  == new_pos  ) CameraMoveFlame = 10;
		CameraMoveFlame++;
	}



	if (CameraMoveFlame > HowFlameMove)
	{
		CameraMoveFlame = 0;
		CamMoveByScript = false;
	}

	
	// X���̃X�e�[�W�̓��O����
	if (g_CameraPos.x - window_half.x <= 0.0f)
	{
		g_CameraPos.x = window_half.x;
	}
	else if (g_CameraPos.x + window_half.x >= WORLD_WIDTH)
	{
		g_CameraPos.x = WORLD_WIDTH - window_half.x;
	}

	// Y���̃X�e�[�W�̓��O����
	if (g_CameraPos.y - window_half.y <= 0.0f)
	{
		g_CameraPos.y = window_half.y;
	}
	else if (g_CameraPos.y + window_half.y >= WORLD_HEIGHT)
	{
		g_CameraPos.y = WORLD_HEIGHT - window_half.y;
	}
}

D3DXVECTOR2 ConvertPositionWorldToScreen(D3DXVECTOR2 pos)
{
	// �J�������W����X�N���[�����W�̌��_�ɕϊ�����
	D3DXVECTOR2 screen_origin_position =
	{
		g_CameraPos.x - SCREEN_WIDTH / 2.0f,
		g_CameraPos.y - SCREEN_HEIGHT / 2.0f
	};

	// ���[���h���W����X�N���[�����W�ɕϊ�����
	D3DXVECTOR2 screen_position = D3DXVECTOR2(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);

	return screen_position;
}



D3DXVECTOR2 getWorldPos() {
	return g_CameraPos;
};

void CameraMove(int power) {
	int X = (rand() % (power * 2)) - power;
	int Y = (rand() % (power * 2)) - power;
	g_CameraPoint.x = X;
	g_CameraPoint.y = Y;
	CameraMoveFlame = 0;
	CamMoveByScript = true;
}


