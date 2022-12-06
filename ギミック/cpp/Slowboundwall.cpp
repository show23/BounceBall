//バウンドが弱くなる壁

#include "main.h"
#include "Slowboundwall.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "Ball.h"


SLOWFLOOR g_Slowboundwall[maxObj];


int slowfloortex;

void InitSlowboundwall()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Slowboundwall[i].use = false;
		g_Slowboundwall[i].speeddown = 0.1f;
	}




	slowfloortex = LoadTexture("data/TEXTURE/slowwall.png");

}


void UninitSlowboundwall()
{
}


void UpdateSlowboundwall()
{
	for (int i = 0; i < maxObj; i++)
	{
		
		if (g_Slowboundwall[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Slowboundwall[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Slowboundwall[i].numObj_Ball);

			
			
			if (w_Pobj->HitPlayer)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう

				
			}

			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				SlowSpeedBall(g_Slowboundwall[i].speeddown);
				
			}
		}
	}
}


void DrawSlowboundwall()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Slowboundwall[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Slowboundwall[i].pos);



			DrawSprite(slowfloortex, screen_pos.x, screen_pos.y, g_Slowboundwall[i].size.x, g_Slowboundwall[i].size.y, 0, 0, 1, 1);
		}
	}
}



void AllClear_Slowboundwall() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Slowboundwall[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Slowboundwall[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Slowboundwall[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			g_Slowboundwall[i].use = false;
		}
	}
}


void setSlowboundwall(D3DXVECTOR2 pos, D3DXVECTOR2 size, float speeddown) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Slowboundwall[i].use)
		{
			g_Slowboundwall[i].use = true;

			pos += size / 2;

			g_Slowboundwall[i].pos = pos;
			g_Slowboundwall[i].size = size;
			g_Slowboundwall[i].speeddown = speeddown;

			g_Slowboundwall[i].numObj_Player = setObj_Player(pos, size, false);

			g_Slowboundwall[i].numObj_Ball = setObj_Ball(pos, size, false, true);
			break;
		}
	}
}



