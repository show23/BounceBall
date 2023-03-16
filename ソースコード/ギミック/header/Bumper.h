#pragma once

#include "main.h"
#include "renderer.h"


struct BUMPER
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// ボール座標
	D3DXVECTOR2				size;			// ボール加速度

	float power;							//飛ばす力

	bool					trigger;		//トリガーにするために使ったやつ

	int popupTimer;							//バンパーがでっかくなる奴

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値
};


void InitBumper();
void UninitBumper();
void UpdateBumper();
void DrawBumper();


void AllClear_Bumper();
void setBumper(D3DXVECTOR2 pos, D3DXVECTOR2 size, float setpower);




