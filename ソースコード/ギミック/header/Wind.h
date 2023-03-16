#pragma once

#include "main.h"
#include "renderer.h"


struct WIND
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �{�[�����W
	D3DXVECTOR2				size;			// �{�[�������x

	float					power;			//���̗�

	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitWind();
void UninitWind();
void UpdateWind();
void DrawWind();

void AllClear_Wind();
void setWind(D3DXVECTOR2 pos, D3DXVECTOR2 size, float power);



