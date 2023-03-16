//バンパー

#include "main.h"
#include "Bumper.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "Ball.h"


BUMPER g_Bumper[maxObj];


float bumperpower = 2.5f;

int Bumpertex;

void InitBumper()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Bumper[i].use = false;
		g_Bumper[i].trigger = false;
		g_Bumper[i].popupTimer = 0;
	}


	Bumpertex = LoadTexture("data/TEXTURE/Bumper.png");

}


void UninitBumper()
{
}


void UpdateBumper()
{
	for (int i = 0; i < maxObj; i++)
	{

		if (g_Bumper[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Bumper[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Bumper[i].numObj_Ball);

			if (g_Bumper[i].popupTimer > 0) g_Bumper[i].popupTimer--;

			if (w_Pobj->HitPlayer)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう

				
			}

			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう

				if (!g_Bumper[i].trigger) {
					Bumper(g_Bumper[i].power);
					g_Bumper[i].popupTimer = 10;
				}
			}
			else {
				g_Bumper[i].trigger = false;
			}
		}
	}
}


void DrawBumper()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Bumper[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Bumper[i].pos);
			DrawSprite(Bumpertex, screen_pos.x, screen_pos.y, g_Bumper[i].size.x + g_Bumper[i].popupTimer, g_Bumper[i].size.y + g_Bumper[i].popupTimer, 0, 0, 1, 1);
		}
	}
}




void AllClear_Bumper() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Bumper[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Bumper[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Bumper[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			g_Bumper[i].use = false;
		}
		g_Bumper[i].trigger = false;
		g_Bumper[i].popupTimer = 0;
	}
}


void setBumper(D3DXVECTOR2 pos, D3DXVECTOR2 size, float setpower) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Bumper[i].use)
		{
			g_Bumper[i].use = true;

			pos += size / 2;

			g_Bumper[i].pos = pos;
			g_Bumper[i].size = size;
			g_Bumper[i].power = setpower;

			g_Bumper[i].numObj_Player = setObj_Player(pos, size, false);
			g_Bumper[i].numObj_Ball = setObj_Ball(pos, size, false, true);
			break;
		}
	}
}


