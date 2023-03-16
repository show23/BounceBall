#pragma once

#include "main.h"
#include "renderer.h"


struct WALL
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 壁座標
	D3DXVECTOR2				size;			// 壁サイズ

	int textype; //0 縁なし 1 フチなし
	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値
};


void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();


void setWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int tex_type);
void AllClear_Wall();
