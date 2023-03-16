#pragma once

#include "main.h"
#include "renderer.h"


struct BREAKABLE_WALL
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �Ǎ��W
	D3DXVECTOR2				size;			// �ǃT�C�Y

	int textype;

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l

	float wallHp;								//�ǂ̗̑�

};


void InitWall_B();
void UninitWall_B();
void UpdateWall_B();
void DrawWall_B();

void AllClear_Wall_B();
void setWall_B(D3DXVECTOR2 pos, D3DXVECTOR2 size, float sethp);
void setStar(D3DXVECTOR2 pos, D3DXVECTOR2 size);
