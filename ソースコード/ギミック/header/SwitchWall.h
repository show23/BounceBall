#pragma once

#include "main.h"
#include "renderer.h"


struct SWITCH_WALL
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos_SW;			// �X�C�b�`���W
	D3DXVECTOR2				size_SW;			// �X�C�b�`�����x

	D3DXVECTOR2				pos_W;			// �Ǎ��W
	D3DXVECTOR2				size_W;			// �ǉ����x

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l


	int W_numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int W_numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l

	float wallHp;								//�ǂ̗̑�

};


void InitSwitch_W();
void UninitSwitch_W();
void UpdateSwitch_W();
void DrawSwitch_W();

void AllClear_Switch();
void setSwitchWall(D3DXVECTOR2 pos_SW, D3DXVECTOR2 size_SW, D3DXVECTOR2 pos_W, D3DXVECTOR2 size_W);