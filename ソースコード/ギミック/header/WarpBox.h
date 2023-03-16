#pragma once

#include "main.h"
#include "renderer.h"


struct WARPBOX
{
	bool					use;			// true:�g���Ă���  false:���g�p
	
	D3DXVECTOR2				pos_enter;			// ���[�v�����W
	D3DXVECTOR2				size_enter;			// ���[�v���T�C�Y

	D3DXVECTOR2				pos_exit;			// ���[�v����W
	D3DXVECTOR2				size_exit;			// ���[�v��T�C�Y

	bool					tp_player;
	bool					tp_ball;

	int numObj_Player;						//�v���C���[Obj�Ƃ��ēo�^����Ă��鐔�l
	int numObj_Ball;						//�{�[����Obj�Ƃ��ēo�^����Ă��鐔�l
};


void InitWarpBox();
void UninitWarpBox();
void UpdateWarpBox();
void DrawWarpBox();

void AllClear_WarpBox();
void setWarpBox(D3DXVECTOR2 pos_ENTER, D3DXVECTOR2 size_ENTER, D3DXVECTOR2 pos_EXIT, D3DXVECTOR2 size_EXIT, bool player_TP, bool ball_TP);


