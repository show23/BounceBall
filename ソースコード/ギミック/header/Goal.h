#pragma once

#include "main.h"
#include "renderer.h"


struct GOAL
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �Ǎ��W
	D3DXVECTOR2				size;			// �ǃT�C�Y

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l

	float wallHp;								//�ǂ̗̑�

};


void InitGoal();
void UninitGoal();
void UpdateGoal();
void DrawGoal();

void AllClear_Goal();
void setGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, float sethp);

