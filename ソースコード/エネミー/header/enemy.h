#pragma once

#include "main.h"
#include "game.h"
#include "renderer.h"


struct ENEMY
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 敵座標
	D3DXVECTOR2				size;			// 敵サイズ
	D3DXVECTOR2				speed;			// 敵スピード

	int numObj_Player;						// プレイヤーObjとして登録されている数値
	int numObj_Ball;						// ボールObjとして登録されている数値

	int Flame;								// 敵フレーム　反転させるときに使う
	int ReverseFlame;						// 動きを反転させるフレーム

	float enemyHp;							// 敵の体力

};


void InitEnemy_B();
void UninitEnemy_B();
void UpdateEnemy_B();
void DrawEnemy_B();

void AllClear_Enemy_B();
void setEnemy_B(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, float sethp, int ReverseFlame);
