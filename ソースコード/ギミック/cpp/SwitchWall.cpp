

#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"
#include "SwitchWall.h"


SWITCH_WALL g_Switch[maxObj];


int switch_walltex;
int switch_switchtex;

float switch_wall_atackmultiply = 5.0f;

void InitSwitch_W()
{
	for (int i = 0; i < maxObj; i++)
	{
		g_Switch[i].use = false;
	}



	//D3DXVECTOR2 pos;
	//D3DXVECTOR2 size;

	//


	//pos = D3DXVECTOR2(500, 3000);
	//size = D3DXVECTOR2(20, 20);

	//g_Switch[0].pos_SW = pos;
	//g_Switch[0].size_SW = size;
	//g_Switch[0].use = true;
	//g_Switch[0].numObj_Player = setObj_Player(pos, size);
	//g_Switch[0].numObj_Ball = setObj_Ball(pos, size, true, true);
	//g_Switch[0].wallHp = 1.0f;

	//pos = D3DXVECTOR2(1000, 3150);
	//size = D3DXVECTOR2(80, 300);

	//g_Switch[0].pos_W = pos;
	//g_Switch[0].size_W = size;
	//g_Switch[0].W_numObj_Player = setObj_Player(pos, size);
	//g_Switch[0].W_numObj_Ball = setObj_Ball(pos, size, false, true);
	//


	

	switch_walltex = LoadTexture("data/TEXTURE/dev_switchwall.png");
	switch_switchtex = LoadTexture("data/TEXTURE/dev_switch.png");

}


void UninitSwitch_W()
{
}


void UpdateSwitch_W()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Switch[i].use)
		{

			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Switch[i].W_numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Switch[i].W_numObj_Ball);

			PLAYER_HIT_OBJ* s_Pobj = getObj_Player(g_Switch[i].numObj_Player);
			BALL_HIT_OBJ* s_Bobj = getObj_Ball(g_Switch[i].numObj_Ball);

			if (s_Pobj->HitPlayer)
			{//‚±‚ñ‚È‚©‚ñ‚¶‚Å“–‚½‚Á‚Ä‚é”»’èŽæ‚ê‚é‚©‚çƒ{[ƒ‹‚Å‚Ì”j‰óˆ—‚Æ‚©‚ÉŽg‚¦‚»‚¤


			}

			if (s_Bobj->HitBall)
			{//‚±‚ñ‚È‚©‚ñ‚¶‚Å“–‚½‚Á‚Ä‚é”»’èŽæ‚ê‚é‚©‚çƒ{[ƒ‹‚Å‚Ì”j‰óˆ—‚Æ‚©‚ÉŽg‚¦‚»‚¤
				float ballspeed = getBall()->ballspeed;

				g_Switch[i].wallHp -= ballspeed * switch_wall_atackmultiply;

				if (g_Switch[i].wallHp <= 0) {

					g_Switch[i].use = false;
					w_Bobj->isUse = false;
					s_Bobj->isUse = false;
					w_Pobj->isUse = false;
					s_Pobj->isUse = false;
				}
				else
				{
					Reflection();
				}
			}



			if (w_Bobj->HitBall)
			{//‚±‚ñ‚È‚©‚ñ‚¶‚Å“–‚½‚Á‚Ä‚é”»’èŽæ‚ê‚é‚©‚çƒ{[ƒ‹‚Å‚Ì”j‰óˆ—‚Æ‚©‚ÉŽg‚¦‚»‚¤
				float ballspeed = getBall()->ballspeed;


				Reflection();
			}
		}
	}
}


void DrawSwitch_W()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Switch[i].use) {

			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Switch[i].pos_SW);


			//‰æ–Ê“à‚ÌŽž‚¾‚¯•`‰æ
			if (screen_pos.x - (g_Switch[i].size_SW.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Switch[i].size_SW.x / 2) > 0 &&
				screen_pos.y - (g_Switch[i].size_SW.y / 2) <= SCREEN_HEIGHT &&
				screen_pos.y + (g_Switch[i].size_SW.y / 2) > 0)
			{
				DrawSprite(switch_switchtex, screen_pos.x, screen_pos.y, g_Switch[i].size_SW.x, g_Switch[i].size_SW.y, 0, 0, 1, 1);
			}

			screen_pos = ConvertPositionWorldToScreen(g_Switch[i].pos_W);

			//‰æ–Ê“à‚ÌŽž‚¾‚¯•`‰æ
			if (screen_pos.x - (g_Switch[i].size_W.x / 2) <= SCREEN_WIDTH &&
				screen_pos.x + (g_Switch[i].size_W.x / 2) > 0 &&
				screen_pos.y - (g_Switch[i].size_W.y / 2) <= SCREEN_HEIGHT &&
				screen_pos.y + (g_Switch[i].size_W.y / 2) > 0)
			{
				DrawSprite(switch_walltex, screen_pos.x, screen_pos.y, g_Switch[i].size_W.x, g_Switch[i].size_W.y, 0, 0, 1, 1);
			}
		}
	}


}



void AllClear_Switch() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Switch[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Switch[i].W_numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Switch[i].W_numObj_Ball);
			PLAYER_HIT_OBJ* s_Pobj = getObj_Player(g_Switch[i].numObj_Player);
			BALL_HIT_OBJ* s_Bobj = getObj_Ball(g_Switch[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			s_Pobj->isUse = false;
			s_Bobj->isUse = false;
			g_Switch[i].use = false;
		}
	}
}

void setSwitchWall(D3DXVECTOR2 pos_SW, D3DXVECTOR2 size_SW, D3DXVECTOR2 pos_W, D3DXVECTOR2 size_W) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Switch[i].use)
		{
			g_Switch[i].use = true;
			
			pos_SW += size_SW / 2;
			
			g_Switch[i].pos_SW = pos_SW;
			g_Switch[i].size_SW = size_SW;

			pos_W += size_W / 2;

			g_Switch[i].pos_W = pos_W;
			g_Switch[i].size_W = size_W;

			g_Switch[i].wallHp = 1;

			g_Switch[i].numObj_Player = setObj_Player(pos_SW, size_SW, false);
			g_Switch[i].numObj_Ball = setObj_Ball(pos_SW, size_SW, false, true);

			g_Switch[i].W_numObj_Player = setObj_Player(pos_W, size_W, false);
			g_Switch[i].W_numObj_Ball = setObj_Ball(pos_W, size_W, false, true);
			break;
		}
	}
}



