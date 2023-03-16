#pragma once

#include "main.h"
#include "renderer.h"


enum ACC_VECTOL {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

struct ACCBLOCK
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �Ǎ��W
	D3DXVECTOR2				size;			// �ǃT�C�Y

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[��Obj�Ƃ��ēo�^����Ă��鐔�l

	ACC_VECTOL				vector;			//����

};


void InitAccelerationBlock();
void UninitAccelerationBlock();
void UpdateAccelerationBlock();
void DrawAccelerationBlock();


void setAccelerationBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, bool trigger, ACC_VECTOL vector);
void AllClear_AccelerationBlock();