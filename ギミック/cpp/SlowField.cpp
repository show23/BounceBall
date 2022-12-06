//スローな地形

#include "main.h"
#include "SlowField.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "Ball.h"


SLOWFIELD g_Slowfield[maxObj];




int slowfieldtex;

void InitSlowfield()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Slowfield[i].use = false;
		g_Slowfield[i].speeddown = 0.1f;
	}
	
	slowfieldtex = LoadTexture("data/TEXTURE/slowfield.png");

}


void UninitSlowfield()
{
}


void UpdateSlowfield()
{
	for (int i = 0; i < maxObj; i++)
	{

		if (g_Slowfield[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Slowfield[i].numObj_Ball);


			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				SlowSpeedBall(g_Slowfield[i].speeddown);

			}
		}
	}
}


void DrawSlowfield()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Slowfield[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Slowfield[i].pos);

			DrawSprite(slowfieldtex, screen_pos.x, screen_pos.y, g_Slowfield[i].size.x, g_Slowfield[i].size.y, 0, 0, 1, 1);
		}
	}
}





void AllClear_Slowfield() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Slowfield[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Slowfield[i].numObj_Ball);
			w_Bobj->isUse = false;
			g_Slowfield[i].use = false;
		}
	}
}


void setSlowfield(D3DXVECTOR2 pos, D3DXVECTOR2 size,float speeddown) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Slowfield[i].use)
		{
			g_Slowfield[i].use = true;

			pos += size / 2;

			g_Slowfield[i].pos = pos;
			g_Slowfield[i].size = size;
			g_Slowfield[i].speeddown = speeddown;


			g_Slowfield[i].numObj_Ball = setObj_Ball(pos, size, false, false);
			break;
		}
	}
}
