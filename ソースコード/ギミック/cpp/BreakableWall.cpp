

#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "score.h"
#include "BreakableWall.h"
#include "effect.h"
#include "sound.h"

BREAKABLE_WALL g_Wall_B[maxObj];

unsigned static int SE_WallBreak;


int dev_B_walltex;
int startex;

float dev_breakable_wall_atackmultiply = 5.0f;

void InitWall_B()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Wall_B[i].use = false;
	}
	SE_WallBreak = LoadSound("data/SE/崖から石がパラパラ落ちる.wav");/////////////////
	SetVolume(SE_WallBreak, 1.0f);

	dev_B_walltex = LoadTexture("data/TEXTURE/Block_Breakable.png");
	//スターの画像指定
	startex = LoadTexture("data/TEXTURE/star.png");
}


void UninitWall_B()
{
}


void UpdateWall_B()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wall_B[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Wall_B[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Wall_B[i].numObj_Ball);


			if (w_Pobj->HitPlayer)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう


			}

			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				float ballspeed = getBall()->ballspeed;

				g_Wall_B[i].wallHp -= ballspeed * dev_breakable_wall_atackmultiply;

				if (g_Wall_B[i].wallHp <= 0) {
					PlaySound(SE_WallBreak, false);
					g_Wall_B[i].use = false;
					w_Bobj->isUse = false;
					w_Pobj->isUse = false;
					SetEffect(getBall()->pos, getBall()->ballspeed * 10.0f);
					CameraMove(3);
					AddScore(10);
				}
				else
				{
					Reflection();
				}
			}
		}
	}
}


void DrawWall_B()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wall_B[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Wall_B[i].pos);


			//画面内の時だけ描画
			if (screen_pos.x - (g_Wall_B[i].size.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Wall_B[i].size.x / 2) > 0				&&
				screen_pos.y - (g_Wall_B[i].size.y / 2) <= SCREEN_HEIGHT&&
				screen_pos.y + (g_Wall_B[i].size.y / 2) > 0)
			{
				DrawSprite(g_Wall_B[i].textype, screen_pos.x, screen_pos.y, g_Wall_B[i].size.x, g_Wall_B[i].size.y, 0, 0, 1, 1);
			}
		}
	}
}

void AllClear_Wall_B() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wall_B[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Wall_B[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Wall_B[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			g_Wall_B[i].textype = dev_B_walltex;
			g_Wall_B[i].use = false;
		}
	}
}

											
void setWall_B(D3DXVECTOR2 pos, D3DXVECTOR2 size,float sethp) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Wall_B[i].use)
		{
			g_Wall_B[i].use = true;
			
			pos += size / 2;

			g_Wall_B[i].pos = pos;
			g_Wall_B[i].size = size;
			g_Wall_B[i].numObj_Player = setObj_Player(pos, size, false);
			g_Wall_B[i].numObj_Ball = setObj_Ball(pos, size, true, true);
			g_Wall_B[i].textype = dev_B_walltex;
			g_Wall_B[i].wallHp = sethp;
			break;
		}
	}
}
void setStar(D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Wall_B[i].use)
		{
			g_Wall_B[i].use = true;

			pos += size / 2;

			g_Wall_B[i].pos = pos;
			g_Wall_B[i].size = size;
			g_Wall_B[i].numObj_Ball = setObj_Ball(pos, size, true, true);
			g_Wall_B[i].textype = startex;
			g_Wall_B[i].wallHp = 1;
			break;
		}
	}
}