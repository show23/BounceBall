#pragma once

#include "main.h"
#include "game.h"
#include "renderer.h"


struct ENEMY
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �G���W
	D3DXVECTOR2				size;			// �G�T�C�Y
	D3DXVECTOR2				speed;			// �G�X�s�[�h

	int numObj_Player;						// �v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						// �{�[��Obj�Ƃ��ēo�^����Ă��鐔�l

	int Flame;								// �G�t���[���@���]������Ƃ��Ɏg��
	int ReverseFlame;						// �����𔽓]������t���[��

	float enemyHp;							// �G�̗̑�

};


void InitEnemy_B();
void UninitEnemy_B();
void UpdateEnemy_B();
void DrawEnemy_B();

void AllClear_Enemy_B();
void setEnemy_B(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, float sethp, int ReverseFlame);
