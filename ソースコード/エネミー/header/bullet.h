#pragma once

#include "main.h"
#include "renderer.h"


struct BULLET
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// 弾座標
	D3DXVECTOR2				size;			// 弾サイズ
	D3DXVECTOR2				speed;			// 弾スピード

	int numObj_Player;						// プレイヤーObjとして登録されている数値

	int Damage;								// ダメージ
};


void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

void AllClear_Bullet();
void setBullet(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, int damage);
