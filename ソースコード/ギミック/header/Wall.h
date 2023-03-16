#pragma once

#include "main.h"
#include "renderer.h"


struct WALL
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �Ǎ��W
	D3DXVECTOR2				size;			// �ǃT�C�Y

	int textype; //0 ���Ȃ� 1 �t�`�Ȃ�
	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();


void setWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int tex_type);
void AllClear_Wall();
