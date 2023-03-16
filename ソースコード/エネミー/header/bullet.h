#pragma once

#include "main.h"
#include "renderer.h"


struct BULLET
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �e���W
	D3DXVECTOR2				size;			// �e�T�C�Y
	D3DXVECTOR2				speed;			// �e�X�s�[�h

	int numObj_Player;						// �v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l

	int Damage;								// �_���[�W
};


void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

void AllClear_Bullet();
void setBullet(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, int damage);
