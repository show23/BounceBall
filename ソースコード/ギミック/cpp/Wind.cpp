//バウンドが弱くなる壁

#include "main.h"
#include "Wind.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "Ball.h"


WIND g_Wind[maxObj];




int windtex;

void InitWind()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Wind[i].use = false;
	}/*


	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	pos = D3DXVECTOR2(20000, 3150);
	size = D3DXVECTOR2(10, 200);

	g_Wind[0].pos = pos;
	g_Wind[0].size = size;
	g_Wind[0].use = true;
	g_Wind[0].numObj_Ball = setObj_Ball(pos, size, true, true);*/



	windtex = LoadTexture("data/TEXTURE/Slowwall.png");

}


void UninitWind()
{
}


void UpdateWind()
{
	for (int i = 0; i < maxObj; i++)
	{

		if (g_Wind[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Wind[i].numObj_Ball);


			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				Wind_Ball(g_Wind[i].power);

			}
		}
	}
}


void DrawWind()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wind[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Wind[i].pos);



			DrawSprite(windtex, screen_pos.x, screen_pos.y, g_Wind[i].size.x, g_Wind[i].size.y, 0, 0, 1, 1);
		}
	}
}



void AllClear_Wind() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wind[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Wind[i].numObj_Ball);
			w_Bobj->isUse = false;
			g_Wind[i].use = false;
		}
	}
}

void setWind(D3DXVECTOR2 pos, D3DXVECTOR2 size, float power) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Wind[i].use)
		{
			g_Wind[i].use = true;

			pos += size / 2;

			g_Wind[i].pos = pos;
			g_Wind[i].size = size;
			g_Wind[i].power = power;
			g_Wind[i].numObj_Ball = setObj_Ball(pos, size, false, true);
			break;
		}
	}
}
