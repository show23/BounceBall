#pragma once

#include "main.h"
#include "renderer.h"


struct SWITCH_WALL
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos_SW;			// スイッチ座標
	D3DXVECTOR2				size_SW;			// スイッチ加速度

	D3DXVECTOR2				pos_W;			// 壁座標
	D3DXVECTOR2				size_W;			// 壁加速度

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールObjとして登録されている数値


	int W_numObj_Player;						//プレイヤーObjとして登録されている数値
	int W_numObj_Ball;						//ボールObjとして登録されている数値

	float wallHp;								//壁の体力

};


void InitSwitch_W();
void UninitSwitch_W();
void UpdateSwitch_W();
void DrawSwitch_W();

void AllClear_Switch();
void setSwitchWall(D3DXVECTOR2 pos_SW, D3DXVECTOR2 size_SW, D3DXVECTOR2 pos_W, D3DXVECTOR2 size_W);