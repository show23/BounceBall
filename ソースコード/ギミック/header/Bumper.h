#pragma once

#include "main.h"
#include "renderer.h"


struct BUMPER
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �{�[�����W
	D3DXVECTOR2				size;			// �{�[�������x

	float power;							//��΂���

	bool					trigger;		//�g���K�[�ɂ��邽�߂Ɏg�������

	int popupTimer;							//�o���p�[���ł������Ȃ�z

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitBumper();
void UninitBumper();
void UpdateBumper();
void DrawBumper();


void AllClear_Bumper();
void setBumper(D3DXVECTOR2 pos, D3DXVECTOR2 size, float setpower);




