#include "main.h"
#include "AccelerationBlock.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"

int g_Score;
int g_OldScore;
unsigned int ScoreTex;
unsigned int Score1Tex;
unsigned int SScoreTex;
unsigned int AScoreTex;
unsigned int BScoreTex;
unsigned int CScoreTex;

int scoreX = 600;
int scoreY = 0;

void InitScore()
{
	ScoreTex = LoadTexture("data/TEXTURE/number.png");
	Score1Tex = LoadTexture("data/TEXTURE/number1.png");
	SScoreTex = LoadTexture("data/TEXTURE/S.png");
	AScoreTex = LoadTexture("data/TEXTURE/A.png");
	BScoreTex = LoadTexture("data/TEXTURE/B.png");
	CScoreTex = LoadTexture("data/TEXTURE/C.png");
	g_Score = 0;
}

void UninitScore()
{
}

void UpdateScore()
{
}

void DrawScore()
{
	int Score;
	Score = g_Score;

	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = Score % 10;
		tx = n % 5 * 0.2f;//xテクスチャ座標
		ty = n / 5 * 0.2f;//yテクスチャ座標
		Score /= 10;

		//ナンバー表示
		float sx, sy;
		sx = 25.0f + 30.0f * (SCORE_FIGURE - 1 - i);//x位置、幅
		sy = 25.0f;//y位置

		DrawSprite(ScoreTex, sx + scoreX, sy + scoreY, 40.0f, 40.0f, tx, ty, 0.2f, 0.2f);
	}
}

void AddScore(int Score)
{
	g_Score += Score;
}

void OldScore(void)
{
	int Score;
	Score = g_Score;
	g_OldScore = g_Score;
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = Score % 10;
		tx = n % 5 * 0.2f;//xテクスチャ座標
		ty = n / 5 * 0.2f;//yテクスチャ座標
		Score /= 10;

		//ナンバー表示
		float sx, sy;
		sx = 540.0f + 30.0f * (SCORE_FIGURE - 1 - i);//x位置、幅
		sy = 378.0f;//y位置

		DrawSprite(Score1Tex, sx, sy, 100.0f, 100.0f, tx, ty, 0.2f, 0.2f);
	}
}


void SetOldScore(int SScore, int AScore, int BScore, int CScore)
{
	if (g_OldScore > SScore)
	{
		DrawSpriteColor(SScoreTex, 450, 340, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldScore > AScore)
	{
		DrawSpriteColor(AScoreTex, 450, 340, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldScore > BScore)
	{
		DrawSpriteColor(BScoreTex, 450, 340, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
	else if (g_OldScore > CScore)
	{
		DrawSpriteColor(CScoreTex, 450, 340, 200.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
}