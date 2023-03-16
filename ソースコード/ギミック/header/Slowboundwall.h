#pragma once

#include "main.h"
#include "renderer.h"


struct SLOWFLOOR
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �{�[�����W
	D3DXVECTOR2				size;			// �{�[�������x

	float					speeddown;		//�����x

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitSlowboundwall();
void UninitSlowboundwall();
void UpdateSlowboundwall();
void DrawSlowboundwall();


void AllClear_Slowboundwall();

void setSlowboundwall(D3DXVECTOR2 pos, D3DXVECTOR2 size, float speeddown);




