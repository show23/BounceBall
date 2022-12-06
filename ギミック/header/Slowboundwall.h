#pragma once

#include "main.h"
#include "renderer.h"


struct SLOWFLOOR
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// ボール座標
	D3DXVECTOR2				size;			// ボール加速度

	float					speeddown;		//減速度

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値
};


void InitSlowboundwall();
void UninitSlowboundwall();
void UpdateSlowboundwall();
void DrawSlowboundwall();


void AllClear_Slowboundwall();

void setSlowboundwall(D3DXVECTOR2 pos, D3DXVECTOR2 size, float speeddown);




