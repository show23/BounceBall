#pragma once

#include "main.h"
#include "renderer.h"


struct WIND
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// ボール座標
	D3DXVECTOR2				size;			// ボール加速度

	float					power;			//風の力

	int numObj_Ball;						//ボールObjとして登録されている数値
};


void InitWind();
void UninitWind();
void UpdateWind();
void DrawWind();

void AllClear_Wind();
void setWind(D3DXVECTOR2 pos, D3DXVECTOR2 size, float power);



