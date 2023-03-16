#pragma once

#include "main.h"
#include "renderer.h"


struct GOAL
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 壁座標
	D3DXVECTOR2				size;			// 壁サイズ

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値

	float wallHp;								//壁の体力

};


void InitGoal();
void UninitGoal();
void UpdateGoal();
void DrawGoal();

void AllClear_Goal();
void setGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, float sethp);

