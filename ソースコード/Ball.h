#pragma once


#include "main.h"
#include "renderer.h"

#define ballH 36
#define ballW 36


#define ball_transam_H 28
#define ball_transam_W 28

#define Ball_TransamMax 12


//�{�[�����������蔻�肪���锠
struct BALL_HIT_OBJ
{
	bool isUse;
	D3DXVECTOR2 objPos;
	D3DXVECTOR2 OldobjPos;
	float objWidth;
	float objHeight;



	//���������ꂽ�肷��A�A�N�V�����̂���ǂ͂���g����
	//�P�ɕǂ⏰�Ƃ��Ďg����I�u�W�F�N�g�Ȃ�K�v�Ȃ���
	float usebuffer;
	//���˂��Ȃ���
	bool objReflection;


	//�ڐG������true�ɂȂ���
	bool HitBall;

	//�ǂ̊p�x
	bool hasvector;
	float vector;
};


struct BALL
{
	bool			use;		// true:�g���Ă���  false:���g�p
	D3DXVECTOR2		pos;		// �{�[�����W
	D3DXVECTOR2		Speed;		// �{�[�������x

	float ballspeed;

};


//*****************************************************************************
// �v���g�^�C�v�錾
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

