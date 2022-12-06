#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "Scroll.h"
#include "enemy.h"
#include "windows.h"
#include "Bullet.h"
#include "score.h"
#include "effect.h"

ENEMY g_Enemy_B[maxObj];

int Enemytex;

float Enemy_atackmultiply = 5.0f;

static int SE_EnemyShoot;
static int SE_EnemyDie;

void InitEnemy_B()
{
	SE_EnemyShoot = LoadSound("data/SE/ショット.wav");
	SE_EnemyDie = LoadSound("data/SE/ロボットを強く殴る2.wav");


	SetVolume(SE_EnemyShoot, 0.5f);
	SetVolume(SE_EnemyDie, 1.0f);

	for (int i = 0; i < maxObj; i++)
	{
		g_Enemy_B[i].use = false;
		g_Enemy_B[i].pos = D3DXVECTOR2(0, 0);
		g_Enemy_B[i].size = D3DXVECTOR2(0, 0);
		g_Enemy_B[i].speed = D3DXVECTOR2(0, 0);
		g_Enemy_B[i].enemyHp = 0;
		g_Enemy_B[i].numObj_Ball = 0;
		g_Enemy_B[i].numObj_Player = 0;
		g_Enemy_B[i].Flame = 0;
		g_Enemy_B[i].ReverseFlame = 0;
	}

	Enemytex = LoadTexture("data/TEXTURE/prototype_enemy_.png");

}


void UninitEnemy_B()
{
}


void UpdateEnemy_B()
{
	
	for (int i = 0; i < maxObj; i++)
	{
		g_Enemy_B[i].Flame++;

		if (g_Enemy_B[i].use)
		{
			if (g_Enemy_B[i].Flame >= g_Enemy_B[i].ReverseFlame) //反転したとき
			{

				D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Enemy_B[i].pos);
				if (screen_pos.x - (g_Enemy_B[i].size.x / 2) <= SCREEN_WIDTH &&
					screen_pos.x + (g_Enemy_B[i].size.x / 2) > 0 &&
					screen_pos.y - (g_Enemy_B[i].size.y / 2) <= SCREEN_HEIGHT &&
					screen_pos.y + (g_Enemy_B[i].size.y / 2) > 0)
				{
					PlaySound(SE_EnemyShoot, 0);
					setBullet(g_Enemy_B[i].pos, g_Enemy_B[i].size, D3DXVECTOR2(g_Enemy_B[i].speed.x, 2.5), 1);
				}
				g_Enemy_B[i].speed.x = g_Enemy_B[i].speed.x * -1;
				g_Enemy_B[i].speed.y = g_Enemy_B[i].speed.y * -1;
				
				g_Enemy_B[i].Flame = 0;
			}
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Enemy_B[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Enemy_B[i].numObj_Ball);

			//加速度系の処理内容を敵座標に還元
			g_Enemy_B[i].pos.x += g_Enemy_B[i].speed.x;
			g_Enemy_B[i].pos.y += g_Enemy_B[i].speed.y;

			UpdateObj_Player(g_Enemy_B[i].numObj_Player, g_Enemy_B[i].pos, g_Enemy_B[i].size);
			UpdateObj_Ball(g_Enemy_B[i].numObj_Ball, g_Enemy_B[i].pos, g_Enemy_B[i].size);



			if (w_Pobj->HitPlayer)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				
				AddPlayerHp(-1);//トリガーにしないと触れている間にフレーム数のダメージを負う
			}

			if (w_Bobj->HitBall)
			{//こんなかんじで当たってる判定取れるからボールでの破壊処理とかに使えそう
				float ballspeed = getBall()->ballspeed;

				g_Enemy_B[i].enemyHp -= ballspeed * Enemy_atackmultiply;

				if (g_Enemy_B[i].enemyHp <= 0) {
					PlaySound(SE_EnemyDie, 0);
					g_Enemy_B[i].use = false;
					w_Bobj->isUse = false;
					w_Pobj->isUse = false;
					AddScore(30);
					SetEffect(g_Enemy_B[i].pos, getBall()->ballspeed * 10.0f);
				}
				else
				{
					Reflection();
				}
			}
		}
	}
}


void DrawEnemy_B()
{
#ifdef _DEBUG
	printf_s("--Enemy------------------------------\n");
	printf_s("Pos: %f, %f\n", g_Enemy_B[0].pos.x, g_Enemy_B[0].pos.y);
	printf_s("Hp: %f\n",g_Enemy_B[0].enemyHp);
	/*printf_s("Pos: %f, %f\n", g_Enemy_B[1].pos.x, g_Enemy_B[1].pos.y);
	printf_s("Hp: %f\n", g_Enemy_B[1].enemyHp);
	printf_s("Pos: %f, %f\n", g_Enemy_B[2].pos.x, g_Enemy_B[2].pos.y);
	printf_s("Hp: %f\n", g_Enemy_B[2].enemyHp);
	printf_s("Pos: %f, %f\n", g_Enemy_B[3].pos.x, g_Enemy_B[3].pos.y);
	printf_s("Hp: %f\n", g_Enemy_B[3].enemyHp);*/
	printf_s("------------------------------------\n\n");
#endif // _DEBUG
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Enemy_B[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Enemy_B[i].pos);


			//画面内の時だけ描画
			if (screen_pos.x - (g_Enemy_B[i].size.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Enemy_B[i].size.x / 2) > 0 &&
				screen_pos.y - (g_Enemy_B[i].size.y / 2) <= SCREEN_HEIGHT &&
				screen_pos.y + (g_Enemy_B[i].size.y / 2) > 0)
			{
				DrawSprite(Enemytex, screen_pos.x, screen_pos.y, g_Enemy_B[i].size.x, g_Enemy_B[i].size.y, 0, 0, 1, 1);
			}
		}
	}
}

void AllClear_Enemy_B() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Enemy_B[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Enemy_B[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Enemy_B[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			g_Enemy_B[i].use = false;
		}
	}
}

//左端の位置(x,y)、大きさ(x,y)、移動速度(x,y)、hp、反転するまでのフレーム数
void setEnemy_B(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 speed, float sethp, int ReverseFlame) 
{

	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Enemy_B[i].use)
		{
			g_Enemy_B[i].use = true;
			g_Enemy_B[i].pos = pos;
			g_Enemy_B[i].size = size;
			g_Enemy_B[i].speed = speed;
			g_Enemy_B[i].enemyHp = sethp;
			g_Enemy_B[i].ReverseFlame = ReverseFlame;

			g_Enemy_B[i].numObj_Player = setObj_Player(pos, size, true);
			g_Enemy_B[i].numObj_Ball = setObj_Ball(pos, size, false, true);
		
			break;
		}
	}
}