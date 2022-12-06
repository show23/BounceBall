

#include "main.h"
#include "Player.h"
#include "Scroll.h"


//ワールド座標
/*
この数値を使ってプレイヤーじゃない奴らを動かす
背景とか台とか
*/
static D3DXVECTOR2 g_CameraPos;
static D3DXVECTOR2 g_CameraPoint;//カメラが動いたときの移動目標

int CameraMoveFlame = 0;
bool CamMoveByScript = false;//カメラがプレイヤーの移動以外で動いたときtrueにする

static int HowFlameMove = 5; //↑の時何フレームカメラを揺らすか

void UpdateCamera(D3DXVECTOR2 new_pos)
{
	D3DXVECTOR2 window_half
	{
		SCREEN_WIDTH / 2.0f,
		SCREEN_HEIGHT / 2.0f
	};

	g_CameraPos = new_pos;
	// 座標更新
	if (CamMoveByScript) {
		g_CameraPos += g_CameraPoint;
		if (g_CameraPos.x > new_pos.x) g_CameraPoint.x += +1.0f;
		if (g_CameraPos.x < new_pos.x) g_CameraPoint.x += -1.0f;
		if (g_CameraPos.y > new_pos.y) g_CameraPoint.y += +1.0f;
		if (g_CameraPos.y < new_pos.y) g_CameraPoint.y += -1.0f;
		if (g_CameraPos  == new_pos  ) CameraMoveFlame = 10;
		CameraMoveFlame++;
	}



	if (CameraMoveFlame > HowFlameMove)
	{
		CameraMoveFlame = 0;
		CamMoveByScript = false;
	}

	
	// X軸のステージの内外判定
	if (g_CameraPos.x - window_half.x <= 0.0f)
	{
		g_CameraPos.x = window_half.x;
	}
	else if (g_CameraPos.x + window_half.x >= WORLD_WIDTH)
	{
		g_CameraPos.x = WORLD_WIDTH - window_half.x;
	}

	// Y軸のステージの内外判定
	if (g_CameraPos.y - window_half.y <= 0.0f)
	{
		g_CameraPos.y = window_half.y;
	}
	else if (g_CameraPos.y + window_half.y >= WORLD_HEIGHT)
	{
		g_CameraPos.y = WORLD_HEIGHT - window_half.y;
	}
}

D3DXVECTOR2 ConvertPositionWorldToScreen(D3DXVECTOR2 pos)
{
	// カメラ座標からスクリーン座標の原点に変換する
	D3DXVECTOR2 screen_origin_position =
	{
		g_CameraPos.x - SCREEN_WIDTH / 2.0f,
		g_CameraPos.y - SCREEN_HEIGHT / 2.0f
	};

	// ワールド座標からスクリーン座標に変換する
	D3DXVECTOR2 screen_position = D3DXVECTOR2(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);

	return screen_position;
}



D3DXVECTOR2 getWorldPos() {
	return g_CameraPos;
};

void CameraMove(int power) {
	int X = (rand() % (power * 2)) - power;
	int Y = (rand() % (power * 2)) - power;
	g_CameraPoint.x = X;
	g_CameraPoint.y = Y;
	CameraMoveFlame = 0;
	CamMoveByScript = true;
}


