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
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 壁座標
	D3DXVECTOR2				size;			// 壁サイズ

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値

	ACC_VECTOL				vector;			//方向

};


void InitAccelerationBlock();
void UninitAccelerationBlock();
void UpdateAccelerationBlock();
void DrawAccelerationBlock();


void setAccelerationBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, bool trigger, ACC_VECTOL vector);
void AllClear_AccelerationBlock();