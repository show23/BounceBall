#pragma once

#include "main.h"
#include "renderer.h"


struct WARPBOX
{
	bool					use;			// true:使っている  false:未使用
	
	D3DXVECTOR2				pos_enter;			// ワープ元座標
	D3DXVECTOR2				size_enter;			// ワープ元サイズ

	D3DXVECTOR2				pos_exit;			// ワープ先座標
	D3DXVECTOR2				size_exit;			// ワープ先サイズ

	bool					tp_player;
	bool					tp_ball;

	int numObj_Player;						//プレイヤーObjとして登録されている数値
	int numObj_Ball;						//ボールにObjとして登録されている数値
};


void InitWarpBox();
void UninitWarpBox();
void UpdateWarpBox();
void DrawWarpBox();

void AllClear_WarpBox();
void setWarpBox(D3DXVECTOR2 pos_ENTER, D3DXVECTOR2 size_ENTER, D3DXVECTOR2 pos_EXIT, D3DXVECTOR2 size_EXIT, bool player_TP, bool ball_TP);


