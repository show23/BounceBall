#pragma once

#include "main.h"
#include "renderer.h"


struct BREAKABLE_WALL
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 壁座標
	D3DXVECTOR2				size;			// 壁サイズ

	int textype;

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値

	float wallHp;								//壁の体力

};


void InitWall_B();
void UninitWall_B();
void UpdateWall_B();
void DrawWall_B();

void AllClear_Wall_B();
void setWall_B(D3DXVECTOR2 pos, D3DXVECTOR2 size, float sethp);
void setStar(D3DXVECTOR2 pos, D3DXVECTOR2 size);
