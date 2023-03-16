

#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "Goal.h"
#include "fade.h"
#include "Clear.h"


GOAL g_Goal[maxObj];



int golatex;

float dev_goal_atackmultiply = 5.0f;

void InitGoal()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Goal[i].use = false;
	}


	golatex = LoadTexture("data/TEXTURE/Block_Goal.png");

}


void UninitGoal()
{
}


void UpdateGoal()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Goal[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Goal[i].numObj_Ball);



			if (w_Bobj->HitBall)
			{//‚±‚ñ‚È‚©‚ñ‚¶‚Å“–‚½‚Á‚Ä‚é”»’èŽæ‚ê‚é‚©‚çƒ{[ƒ‹‚Å‚Ì”j‰óˆ—‚Æ‚©‚ÉŽg‚¦‚»‚¤
				float ballspeed = getBall()->ballspeed;

				g_Goal[i].wallHp -= ballspeed * dev_goal_atackmultiply;

				if (g_Goal[i].wallHp <= 0) {

					g_Goal[i].use = false;
					w_Bobj->isUse = false;

					SetOldScene();
					VolumeLow();
					SceneTransition(SCENE_CLEAR_next);
				}
				else
				{
					
				}
			}
		}
	}
}


void DrawGoal()
{
#ifdef _DEBUG
	printf_s("--GOAL----------------------------\n");
	printf_s("Pos: %f, %f\n", g_Goal[0].pos.x, g_Goal[0].pos.y);
	
	printf_s("------------------------------------\n\n");
#endif // _DEBUG
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Goal[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Goal[i].pos);


			//‰æ–Ê“à‚ÌŽž‚¾‚¯•`‰æ
			if (screen_pos.x - (g_Goal[i].size.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Goal[i].size.x / 2) > 0 &&
				screen_pos.y - (g_Goal[i].size.y / 2) <= SCREEN_HEIGHT &&
				screen_pos.y + (g_Goal[i].size.y / 2) > 0)
			{
				DrawSprite(golatex, screen_pos.x, screen_pos.y, g_Goal[i].size.x, g_Goal[i].size.y, 0, 0, 1, 1);
			}
		}
	}
}

void AllClear_Goal() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Goal[i].use)
		{
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Goal[i].numObj_Ball);
			w_Bobj->isUse = false;
			g_Goal[i].use = false;
		}
	}
}


void setGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, float sethp) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Goal[i].use)
		{
			g_Goal[i].use = true;

			pos += size / 2;

			g_Goal[i].pos = pos;
			g_Goal[i].size = size;
			g_Goal[i].numObj_Ball = setObj_Ball(pos, size, true, true);
			g_Goal[i].wallHp = sethp;
			break;
		}
	}
}

