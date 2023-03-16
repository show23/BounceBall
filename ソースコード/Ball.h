#pragma once


#include "main.h"
#include "renderer.h"

#define ballH 36
#define ballW 36


#define ball_transam_H 28
#define ball_transam_W 28

#define Ball_TransamMax 12


//ボール向け当たり判定が入る箱
struct BALL_HIT_OBJ
{
	bool isUse;
	D3DXVECTOR2 objPos;
	D3DXVECTOR2 OldobjPos;
	float objWidth;
	float objHeight;



	//動いたり壊れたりする、アクションのある壁はこれ使って
	//単に壁や床として使われるオブジェクトなら必要ないよ
	float usebuffer;
	//反射しない壁
	bool objReflection;


	//接触した時trueになるやつ
	bool HitBall;

	//壁の角度
	bool hasvector;
	float vector;
};


struct BALL
{
	bool			use;		// true:使っている  false:未使用
	D3DXVECTOR2		pos;		// ボール座標
	D3DXVECTOR2		Speed;		// ボール加速度

	float ballspeed;

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT  InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);
void setBallSpeed(float x, float y);
void SpeedDown_Ball();
void ResetSpeedBall();
void SlowSpeedBall(float speeddown);
void Bumper(float power);
void Wind_Ball(float power);
void Warp_Ball(D3DXVECTOR2 pos);

void setBall(D3DXVECTOR2 POS, D3DXVECTOR2 SPEED);
BALL* getBall(void);

BALL_HIT_OBJ* getObj_Ball(int num);


void UpdateObj_Ball(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size);

int setObj_Ball(D3DXVECTOR2 position, D3DXVECTOR2 size, bool useBuffer, bool reflection);
void DestroyObj_Ball(int objnum);

void Reflection();

