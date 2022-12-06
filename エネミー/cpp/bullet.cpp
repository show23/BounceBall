#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "Scroll.h"
#include "bullet.h"
#include "windows.h"

BULLET g_Bullet[maxObj];

int Bullettex;

float Bullet_atackmultiply = 5.0f;

void InitBullet()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].pos = D3DXVECTOR2(0, 0);
		g_Bullet[i].size = D3DXVECTOR2(0, 0);
		g_Bullet[i].speed = D3DXVECTOR2(0, 0);
		g_Bullet[i].numObj_Player = 0;
		g_Bullet[i].Damage = 0;
	}
	Bullettex = LoadTexture("data/TEXTURE/enemy_bullet.png");
}


void UninitBullet()
{
}


void UpdateBullet()
{

	for (int i = 0; i < maxObj; i++)
	{
		//g_Bullet[i].Flame++;

		if (g_Bullet[i].use)
		{
			
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Bullet[i].numObj_Player);

			//加速度系の処理内容を敵座標に還元
			g_Bullet[i].pos.x += g_Bullet[i].speed.x;
			g_Bullet[i].pos.y += g_Bullet[i].speed.y;

			UpdateObj_Player(g_Bullet[i].numObj_Player, g_Bullet[i].pos, g_Bullet[i].size);



			if (w_Pobj->HitPlayer)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう

				AddPlayerHp(-g_Bullet[i].Damage);
				w_Pobj->isUse = false;
				g_Bullet[i].use = false;
			}

		}
	}
}


void DrawBullet()
{
#ifdef _DEBUG
	printf_s("--Bullet------------------------------\n");
	printf_s("Pos: %f, %f\n", g_Bullet[0].pos.x, g_Bullet[0].pos.y);
	printf_s("Speed: %f,%f\n", g_Bullet[0].speed.x, g_Bullet[0].speed.y);
	//printf_s("damage : %s\n", g_Bullet[0].Damage);
	printf_s("------------------------------------\n\n");
#endif // _DEBUG
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Bullet[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Bullet[i].pos);


			//画面内の時だけ描画
			if (screen_pos.x - (g_Bullet[i].size.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Bullet[i].size.x / 2) > 0 &&
				screen_pos.y - (g_Bullet[i].size.y / 2) <= SCREEN_HEIGHT &&
				screen_pos.y + (g_Bullet[i].size.y / 2) > 0)
			{
				DrawSprite(Bullettex, screen_pos.x, screen_pos.y, g_Bullet[i].size.x, g_Bullet[i].size.y, 0, 0, 1, 1);
			}
			else
			{
				g_Bullet[i].use = false;
			}
		}
	}
}

void AllClear_Bullet() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Bullet[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Bullet[i].numObj_Player);
			w_Pobj->isUse = false;
			g_Bullet[i].use = false;
		}
	}
}

//左端の位置(x,y)、大きさ(x,y)、移動速度(x,y)
void setBullet(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, int damage)
{

	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Bullet[i].use)
		{
			g_Bullet[i].use = true;
			g_Bullet[i].pos = pos;
			g_Bullet[i].size = size / 4;
			g_Bullet[i].speed = speed * 2;
			g_Bullet[i].Damage = damage;

			g_Bullet[i].numObj_Player = setObj_Player(pos, size, true);

			break;
		}
	}
}