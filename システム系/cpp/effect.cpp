#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "Enemy.h"
#include "effect.h"
#include "Scroll.h"

EFFECT g_effect[MAX_EFFECT];//実体
unsigned int g_EffectTexture;//テクスチャID
void AllClear_Effect();

//初期化
void InitEffect()
{
	g_EffectTexture = LoadTexture("data/TEXTURE/block destruction effect.png");

	AllClear_Effect();
}

//終了
void UninitEffect()
{
	
}

//更新
void UpdateEffect()
{
	for (int effectCnt = 0; effectCnt < MAX_EFFECT; effectCnt++)
	{
		if (g_effect[effectCnt].isUse == true)
		{
			g_effect[effectCnt].flame++;

			if (g_effect[effectCnt].flame >= 4)
			{
				g_effect[effectCnt].isUse = false;
			}
		}
	}
}

//描画
void DrawEffect()
{

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].isUse)
		{

			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_effect[i].pos);
			DrawSprite
			(	g_EffectTexture,
				screen_pos.x, screen_pos.y,
				g_effect[i].size, g_effect[i].size,
				g_effect[i].flame % 2 * 0.5f,
				g_effect[i].flame / 2 * 0.5f,
				0.5f,0.5f
			);
		}
	}
}
//Get関数
EFFECT* GetEffect()
{
	return &g_effect[0];
}

//Set関数
void SetEffect(D3DXVECTOR2 pos, float size)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (!g_effect[i].isUse)
		{
			g_effect[i].pos = pos;
			g_effect[i].size = size;
			g_effect[i].flame = 0;
			g_effect[i].isUse = true;

			break;
		}
	}
}


void AllClear_Effect()
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_effect[i].size = 0.0f;
		g_effect[i].isUse = false;
		g_effect[i].flame = 0;
	}
}