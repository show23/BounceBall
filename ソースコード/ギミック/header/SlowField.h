#pragma once

#include "main.h"
#include "renderer.h"


struct SLOWFIELD
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �{�[�����W
	D3DXVECTOR2				size;			// �{�[�������x

	float					speeddown;
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitSlowfield();
void UninitSlowfield();
void UpdateSlowfield();
void DrawSlowfield();


void AllClear_Slowfield();


void setSlowfield(D3DXVECTOR2 pos, D3DXVECTOR2 size, float speeddown);



