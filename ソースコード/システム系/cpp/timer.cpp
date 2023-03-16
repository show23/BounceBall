#include "main.h"
#include "AccelerationBlock.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "timer.h"
#include "fade.h"
#include "sound.h"

int g_Timer;
int g_OldTimer;
unsigned int TimerTex;
unsigned int TimerResultTex;

unsigned int STex;
unsigned int ATex;
unsigned int BTex;
unsigned int CTex;

void InitTimer()
{
	TimerResultTex = LoadTexture("data/TEXTURE/number1.png");
	TimerTex = LoadTexture("data/TEXTURE/number.png");

	STex = LoadTexture("data/TEXTURE/S.png");
	ATex = LoadTexture("data/TEXTURE/A.png");
	BTex = LoadTexture("data/TEXTURE/B.png");
	CTex = LoadTexture("data/TEXTURE/C.png");
	g_Timer = 100;
}


void UninitTimer()
{
}

void UpdateTimer()
{
	if (g_Timer <= 0)
	{
		SetOldScene();
		VolumeLow();
		SceneTransition(SCENE_GAMEOVER_cont);
		StopSoundAll();
	}
}

void DrawTimer()
{
	int Timer;
	Timer = g_Timer;
	
	for (int i = 0; i < TIMER_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = Timer % 10;
		tx = n % 5 * 0.2f ;//xテクスチャ座標
		ty = n / 5 * 0.2f ;//yテクスチャ座標
		Timer /= 10;

		//ナンバー表示
		float sx, sy;
		sx = 1200.0f + 30.0f * (TIMER_FIGURE - 1 - i);//x位置、幅
		sy = 25.0f;//y位置

		DrawSprite(TimerTex,sx,sy,40.0f,40.0f, tx, ty, 0.2f, 0.2f);
	}
}

void AddTimer(int Time)
{
	g_Timer += Time;
}

void SetTimer(int Time)
{
	g_Timer = Time;
}

void getOldTime(void)
{
	int Timer;
	Timer = g_Timer;
	g_OldTimer = g_Timer;

	for (int i = 0; i < TIMER_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = Timer % 10;
		tx = n % 5 * 0.2f;//xテクスチャ座標
		ty = n / 5 * 0.2f;//yテクスチャ座標
		Timer /= 10;

		//ナンバー表示
		float sx, sy;
		sx = 570.0f + 30.0f * (TIMER_FIGURE - 1 - i);//x位置、幅
		sy = 170.0f;//y位置

		DrawSpriteColor(TimerResultTex, sx, sy, 100.0f, 100.0f, tx, ty, 0.2f, 0.2f, D3DXCOLOR(1.0,1.0,1.0, 1.0));
	}
	
}


void SetOldTime(int STimer, int ATimer, int BTimer, int CTimer)
{

	if (g_OldTimer > STimer)
	{
		DrawSpriteColor(STex, 450, 130, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldTimer > ATimer)
	{
		DrawSpriteColor(ATex, 450, 130, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldTimer > BTimer)
	{
		DrawSpriteColor(BTex, 450, 130, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldTimer > CTimer)
	{
		DrawSpriteColor(CTex, 450, 130, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
}