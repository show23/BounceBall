#pragma once

#include "main.h"
#include "renderer.h"


struct SLOWFIELD
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// ボール座標
	D3DXVECTOR2				size;			// ボール加速度

	float					speeddown;
	int numObj_Ball;						//ボールObjとして登録されている数値
};


void InitSlowfield();
void UninitSlowfield();
void UpdateSlowfield();
void DrawSlowfield();


void AllClear_Slowfield();


void setSlowfield(D3DXVECTOR2 pos, D3DXVECTOR2 size, float speeddown);



