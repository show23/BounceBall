
#include "main.h"
#include "AccelerationBlock.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "Scroll.h"


ACCBLOCK g_AccelerationBlock[maxObj];

int AccelerationBlockTex;
static int flame;

void InitAccelerationBlock()
{
	AllClear_AccelerationBlock();

	AccelerationBlockTex = LoadTexture("data/TEXTURE/MoveBlock.png");
}


void UninitAccelerationBlock()
{
}

//ボールの加速はボールの速度に依存
//プレイヤーの加速は速度固定(歩きは5.6、走りは10)


void UpdateAccelerationBlock()
{

	for (int i = 0; i < maxObj; i++)
	{
		if (g_AccelerationBlock[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_AccelerationBlock[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_AccelerationBlock[i].numObj_Ball);

			if (w_Pobj->HitPlayer)
			{
				switch (g_AccelerationBlock[i].vector)
				{
				case RIGHT:
					setPlayerSpeed(100, -5);
					break;
				case LEFT:
					setPlayerSpeed(-100, -5);
					break;
				case UP:
					setPlayerSpeed(0, -100);
					break;
				case DOWN:
					setPlayerSpeed(0, 95);
					break;
				}
				setPlayerOnGround(false);
			}

			if (w_Bobj->HitBall)
			{
				switch (g_AccelerationBlock[i].vector)
				{
				case RIGHT:
					setBallSpeed(20, 0);
					break;
				case LEFT:
					setBallSpeed(-20, 0);
					break;
				case UP:
					setBallSpeed(0, -20);
					break;
				case DOWN:
					setBallSpeed(0, 20);
					break;
				}
			}
		}
	}
}


void DrawAccelerationBlock()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_AccelerationBlock[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_AccelerationBlock[i].pos);

			DrawSprite(AccelerationBlockTex, screen_pos.x, screen_pos.y, g_AccelerationBlock[i].size.x, g_AccelerationBlock[i].size.y, 0, 0, 1, 1);
			
			float Rotate = 0.0f;

			switch (g_AccelerationBlock[i].vector)
			{
			case RIGHT:
				Rotate = 0.0f;
				break;
			case DOWN:
				Rotate = 90.0f;
				break;
			case LEFT:
				Rotate = 180.0f;
				break;
			case UP:
				Rotate = 270.0f;
				break;
			}
			Rotate = Rotate * (M_PI / 180.00f);
			DrawSpriteColorRotate(AccelerationBlockTex, screen_pos.x, screen_pos.y, g_AccelerationBlock[i].size.x, g_AccelerationBlock[i].size.y,
				0, 0, 1, 1, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), Rotate);
		}
	}
}

void AllClear_AccelerationBlock() {
	for (int i = 0; i < maxObj; i++)
	{
		if(g_AccelerationBlock[i].use){
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_AccelerationBlock[i].numObj_Player);
			w_Pobj->isUse = false;
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_AccelerationBlock[i].numObj_Ball);
			w_Bobj->isUse = false;
		}
			g_AccelerationBlock[i].use = false;
	}
}

void setAccelerationBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, bool trigger,ACC_VECTOL vector) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_AccelerationBlock[i].use)
		{
			pos += size / 2;

			g_AccelerationBlock[i].use = true;
			g_AccelerationBlock[i].pos = pos;
			g_AccelerationBlock[i].size = size;

			g_AccelerationBlock[i].vector = vector;

			g_AccelerationBlock[i].numObj_Player = setObj_Player(pos, size, trigger);
			g_AccelerationBlock[i].numObj_Ball = setObj_Ball(pos, size, true, true);
			break;
		}
	}
}