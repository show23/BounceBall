

#include "main.h"
#include "WarpBox.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "Scroll.h"
#include "sound.h"


WARPBOX g_WarpBox[maxObj];


int warpplayertex;
unsigned static int SE_warpBox;


void InitWarpBox()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_WarpBox[i].use = false;
	}



	SE_warpBox = LoadSound("data/SE/高速移動.wav");
	SetVolume(SE_warpBox, 1.0f);

	warpplayertex = LoadTexture("data/TEXTURE/dev_warp.png");

}


void UninitWarpBox()
{
}


void UpdateWarpBox()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_WarpBox[i].use)
		{
			if (g_WarpBox[i].tp_player)
			{
				PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_WarpBox[i].numObj_Player);
				if (w_Pobj->HitPlayer)
				{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
					Warp_Player(g_WarpBox[i].pos_exit);
					PlaySound(SE_warpBox, 0);
				}
			}

			if (g_WarpBox[i].tp_ball)
			{
				BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_WarpBox[i].numObj_Ball);
				if (w_Bobj->HitBall)
				{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
					Warp_Ball(g_WarpBox[i].pos_exit);
					PlaySound(SE_warpBox, 0);
				}
			}

		}
	}
}


void DrawWarpBox()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_WarpBox[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_WarpBox[i].pos_enter);
			DrawSprite(warpplayertex, screen_pos.x, screen_pos.y, g_WarpBox[i].size_enter.x, g_WarpBox[i].size_enter.y, 0, 0, 1, 1);

			screen_pos = ConvertPositionWorldToScreen(g_WarpBox[i].pos_exit);
			DrawSprite(warpplayertex, screen_pos.x, screen_pos.y, g_WarpBox[i].size_exit.x, g_WarpBox[i].size_exit.y, 0, 0, 1, 1);
		}
	}
}



void AllClear_WarpBox(){
	for (int i = 0; i < maxObj; i++)
	{
		if (g_WarpBox[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_WarpBox[i].numObj_Player);
			w_Pobj->isUse = false;
			g_WarpBox[i].use = false;
		}
	}
}

void setWarpBox(D3DXVECTOR2 pos_ENTER, D3DXVECTOR2 size_ENTER, D3DXVECTOR2 pos_EXIT, D3DXVECTOR2 size_EXIT, bool player_TP, bool ball_TP) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_WarpBox[i].use)
		{
			g_WarpBox[i].use = true;
			pos_ENTER += size_ENTER / 2;
			pos_EXIT += size_EXIT / 2;


			g_WarpBox[i].pos_enter = pos_ENTER;
			g_WarpBox[i].size_enter = size_ENTER;
				  
			g_WarpBox[i].pos_exit = pos_EXIT;
			g_WarpBox[i].size_exit = size_EXIT;

			g_WarpBox[i].tp_player = player_TP;
			g_WarpBox[i].tp_ball = ball_TP;

			g_WarpBox[i].numObj_Player = setObj_Player(pos_ENTER, size_ENTER ,true);
			g_WarpBox[i].numObj_Ball = setObj_Ball(pos_ENTER, size_ENTER,true,true);
			break;
		}
	}
}
