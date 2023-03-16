
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Ball.h"
#include "sound.h"
#include "game.h"
#include "effect.h"

#include "Scroll.h"

//-----------------------------
//�O���[�o���ϐ��錾
//-------------------------------

//�\����
BALL g_Ball;//�{�[���̃I�u�W�F�N�g
BALL_HIT_OBJ  b_Obj[maxObj];//�{�[���Ƃ̓����蔻������I�u�W�F�N�g
//�e�N�X�`��
int balltex;
int balltex_transam;


//�c���o����I

bool doTransam = true;
D3DXVECTOR2 Ball_Transam[Ball_TransamMax];



//------------------------------------------------------
//�ύX�\�萔//////�Ȃ񂩋C�ɂȂ�Ȃ炢������Ă��
//------------------------------------------------------
//
float ball_Rotate = 0.0f;
//x������~��
float ball_XMASATU = 0.10f;

//�d�͉����x
float BallGravity = 0.4f;

//�{�[���̏d�͉����J�n���x
float BallStartGrav = 15.0f;

//�{�[�����˓x
float Ball_bounce = 1.0f;

//�d�͉����x�ő�l
float B_AccYmax = 10.0f;

//�{�[������(1���Ɗ��S��~����Ǝv�� 0�Ŗ�����)
float Ball_speeddown_multiply = 0.05f;

//�Ǔ��Փˎ��̃{�[�������x
float Ball_speeddown_onHit = 1;

//�{�[���̌���(��)
float Ball_speeddown_Plot = 0.991f;

//�Ǌђʖh�~�p�̑��x�̍ő�l�ݒ�
float MaxBallSpeed = 30.0f;

//�{�[���̒��˂���E���x
//�Ȃ�Ƃ������A�{�[���̈ړ��ʂ��[���Ƃ݂Ȃ����̔�r�Ɏg���l
//����Ȃ��Ƃ�΂�
//Y���W�Ƃ��ׂ����ݒ肵�Ȃ��Ƃ����ƍׂ����т��т�񒵂˂�
float Ball_minBounceSpeedY = 1.2f;

//�v�Z�p�̂Ȃɂ�
D3DXVECTOR2 position_buffer;
D3DXVECTOR2 speed_buffer;

//-----------------------------------
//�Ȃ񂿂��錾
//---------------------------------

//�����x���Z�b�g
//Unity�łł�R�L�[�̃{�[���ʒu���Z�b�g�̎��Ɏg���Ă�����
//�{�[�����������Ƃ��Ƃ��Ɏg���邩��

void ResetSpeedBall();

//�ǂɓ��������Ƃ��̌����̊֐�
void SpeedDown_Ball();


void Reflection();


HRESULT InitBall(void)
{
	balltex = LoadTexture("data/TEXTURE/ball.png");
	balltex_transam = LoadTexture("data/TEXTURE/ball_transam.png");

	//------------
	//������
	//------------


	//�ʒu--------
	g_Ball.pos.x = 0;
	g_Ball.pos.y = 0;
	
	//���x--------
	g_Ball.Speed.x = 0;
	g_Ball.Speed.y = 0;
	//





	for (int i = 0; i < maxObj; i++)
	{
		b_Obj[i].isUse = false;
		b_Obj[i].HitBall = false;
		b_Obj[i].objReflection = true;
		b_Obj[i].usebuffer = false;
		b_Obj[i].hasvector = false;
	}

	for (int i = 0; i < Ball_TransamMax; i++)
	{
		Ball_Transam[i] = D3DXVECTOR2(0.0f, 0.0f);
	}



	return E_NOTIMPL;
}

void UninitBall(void)
{


}

void UpdateBall(void)
{
	if (g_Ball.use) {


		//�{�[���̏d�͉�������
		if (g_Ball.ballspeed <= BallStartGrav) {

			if (g_Ball.Speed.y <= B_AccYmax)
			{
				g_Ball.Speed.y += BallGravity;
			}
		}

		if (g_Ball.Speed.x >= MaxBallSpeed) g_Ball.Speed.x = MaxBallSpeed;
		if (g_Ball.Speed.x <= -MaxBallSpeed) g_Ball.Speed.x = -MaxBallSpeed;

		if (g_Ball.Speed.y >= MaxBallSpeed) g_Ball.Speed.y = MaxBallSpeed;
		if (g_Ball.Speed.y <= -MaxBallSpeed) g_Ball.Speed.y = -MaxBallSpeed;


		g_Ball.ballspeed = (fabsf(g_Ball.Speed.x) + fabsf(g_Ball.Speed.y)) / 2.00000000f;

		ball_Rotate = -g_Ball.Speed.x * 5;
		//�v�Z�p�̌Â��ʒu���
		D3DXVECTOR2 oldpos = g_Ball.pos;

		//�����x�n�̏������e�����W�ɊҌ�
		g_Ball.pos.x += g_Ball.Speed.x;
		g_Ball.pos.y += g_Ball.Speed.y;

		//�{�[����������--------------------------------------------------------------
		float speedmultiply = 1;
		//�v���g
		speedmultiply = Ball_speeddown_Plot;

		g_Ball.Speed = g_Ball.Speed * speedmultiply;

		//�X�N���[���ł̔���----------------------------------------------------------
		//��ʂƂ̓����蔻�����肽���̂ŃX�N���[�����W�Ɉ�x�ϊ����Ĕ��肵�܂�
		D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Ball.pos);
		D3DXVECTOR2 world_pos = getWorldPos();

		//��ʂ̉E���ɓ��������Ƃ�
		if (screen_pos.x + (ballW / 2) > SCREEN_WIDTH)
		{
			SpeedDown_Ball();
			
			g_Ball.pos.x = (SCREEN_WIDTH - ballW) / 2 + world_pos.x;
			g_Ball.Speed.x = -g_Ball.Speed.x;
		}

		//��ʂ̍����ɓ��������Ƃ�
		if (screen_pos.x - (ballW / 2) < 0)
		{
			SpeedDown_Ball();
			g_Ball.pos.x = world_pos.x + ((-SCREEN_WIDTH + ballW) / 2);
			g_Ball.Speed.x = -g_Ball.Speed.x;
		}

		//��ʂ̉����ɓ��������Ƃ�
		if (screen_pos.y + (ballH / 2) > SCREEN_HEIGHT)
		{
			SpeedDown_Ball();
			g_Ball.pos.y = (SCREEN_HEIGHT - ballH) / 2 + world_pos.y;
			g_Ball.Speed.y = -g_Ball.Speed.y;

			//�U���ጸ(�������Ɉړ�)
			if (fabsf(g_Ball.Speed.y) < Ball_minBounceSpeedY)
			{
				g_Ball.Speed.y = 0;
			}
		}

		//��ʂ̏㑤�ɓ��������Ƃ�
		if (screen_pos.y - (ballH / 2) < 0)
		{
			SpeedDown_Ball();
			g_Ball.pos.y = world_pos.y + ((-SCREEN_HEIGHT + ballH) / 2);
			g_Ball.Speed.y = -g_Ball.Speed.y;
		}

		/////�I�u�W�F�N�g�Ƃ̓����蔻��--------------------------------------------------------------

		//�o�b�t�@
		//���t���N�V������true�ŃZ�b�g����Ă���I�u�W�F�N�g������Ƃ�Refrection���Ă񂾎��ɔ��˂���悤�ɂȂ��Ă܂�
		//1�t���[���ŕǂ��󂵁A����ɔ��˂��Ȃ��Ƃ�������������悤

		speed_buffer = g_Ball.Speed;
		position_buffer = g_Ball.pos;

		for (int i = 1; i < maxObj; i++)
		{
			if (b_Obj[i].isUse)
			{
				b_Obj[i].HitBall = false;
				bool moved = false;

				D3DXVECTOR2 ObjPOS = b_Obj[i].objPos;
				if (b_Obj[i].objPos != b_Obj[i].OldobjPos)
				{
					ObjPOS = b_Obj[i].OldobjPos;
				}


				//X���Ɍ�������ꏊ������Ƃ�
				if (g_Ball.pos.x + (ballW / 2) >= b_Obj[i].objPos.x - (b_Obj[i].objWidth / 2) &&
					g_Ball.pos.x - (ballW / 2) <= b_Obj[i].objPos.x + (b_Obj[i].objWidth / 2))
				{
					//Y���W���߂荞��łĂ����S��荂���ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Ball.pos.y - (ballH / 2) <= b_Obj[i].objPos.y + (b_Obj[i].objHeight / 2) &&
						oldpos.y - (ballH / 2) >= ObjPOS.y + (b_Obj[i].objHeight / 2))
					{
						if (!moved && b_Obj[i].objReflection) 
						{
							speed_buffer.y *= -1;
							position_buffer.y = b_Obj[i].objPos.y + ((b_Obj[i].objHeight + ballH) / 2);
							moved = true;
							if (!b_Obj[i].usebuffer) 
							{
								Reflection();
							}
						}
						b_Obj[i].HitBall = true;
					}

					//Y���W���߂荞��łĂ����S���Ⴂ�ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Ball.pos.y + (ballH / 2) >= b_Obj[i].objPos.y - (b_Obj[i].objHeight / 2) &&
						oldpos.y + (ballH / 2) <= ObjPOS.y - (b_Obj[i].objHeight / 2))
					{
						if (!moved && b_Obj[i].objReflection) 
						{
							position_buffer.y = b_Obj[i].objPos.y - ((b_Obj[i].objHeight + ballH) / 2);
							speed_buffer.y *= -1;
							moved = true;
							if (!b_Obj[i].usebuffer) 
							{
								Reflection();
							}
						}
						b_Obj[i].HitBall = true;
					}
				}


				//Y���Ɍ�������ꏊ������Ƃ�
				if (g_Ball.pos.y + (ballH / 2) >= b_Obj[i].objPos.y - (b_Obj[i].objHeight / 2) &&
					g_Ball.pos.y - (ballH / 2) <= b_Obj[i].objPos.y + (b_Obj[i].objHeight / 2))
				{
					//X���W���߂荞��łĂ����S��荂���ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Ball.pos.x - (ballW / 2) <= b_Obj[i].objPos.x + (b_Obj[i].objWidth / 2) &&
						oldpos.x - (ballW / 2) >= ObjPOS.x + (b_Obj[i].objWidth / 2))
					{
						if (!moved && b_Obj[i].objReflection) {
							position_buffer.x = b_Obj[i].objPos.x + ((b_Obj[i].objWidth + ballW) / 2);
							speed_buffer.x *= -1;
							moved = true;
							if (!b_Obj[i].usebuffer) 
							{
								Reflection();
							}
						}
						b_Obj[i].HitBall = true;
					}

					//X���W���߂荞��łĂ����S���Ⴂ�ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Ball.pos.x + (ballW / 2) >= b_Obj[i].objPos.x - (b_Obj[i].objWidth / 2) &&
						oldpos.x + (ballW / 2) <= ObjPOS.x - (b_Obj[i].objWidth / 2))
					{
						if (!moved && b_Obj[i].objReflection) {
							position_buffer.x = b_Obj[i].objPos.x - ((b_Obj[i].objWidth + ballW) / 2);
							speed_buffer.x *= -1;
							moved = true;
							if (!b_Obj[i].usebuffer) 
							{
								Reflection();
							}
						}
						b_Obj[i].HitBall = true;
					}
				}


				b_Obj[i].OldobjPos = b_Obj[i].objPos;
			}
		}
	}
}


void setBallSpeed(float x, float y) {
	g_Ball.Speed.x = x;
	g_Ball.Speed.y = y;
}

//�{�[�������ʒu�Ƀ��[�v������Ƃ����͂�����Ă΂Ȃ��Ƃ��̂܂܂̑��x�Ő������ł����̂Œ���
void ResetSpeedBall() {
	g_Ball.Speed.x = 0;
	g_Ball.Speed.y = 0;
}

void UpdateObj_Ball(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size) {
	b_Obj[ObjectID].objPos = position;
	b_Obj[ObjectID].objWidth = size.x;
	b_Obj[ObjectID].objHeight = size.y;
	//�g���Ă�obj�ԍ����ꉞ�Ԃ�(Destroy�Ƃ��ړ�����ǂɎg���Ă�)
	return;
}


//�ǂɓ������Č�������֐�
void SpeedDown_Ball() 
{
	g_Ball.Speed.x = g_Ball.Speed.x * Ball_speeddown_onHit;
	if (fabsf(g_Ball.Speed.y) >= Ball_minBounceSpeedY) {
		g_Ball.Speed.y = g_Ball.Speed.y * Ball_speeddown_onHit;
	}
}


void DrawBall(void)
{
	if (g_Ball.use)
	{

		if (doTransam) {
			for (int i = 0; i < Ball_TransamMax; i++)
			{
				Ball_Transam[Ball_TransamMax - i] = Ball_Transam[Ball_TransamMax - (i+1)];
			}
			
			Ball_Transam[0] = g_Ball.pos;

		}


		if (doTransam)
		{
			for (int i = 0; i < Ball_TransamMax; i++)
			{
				D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(Ball_Transam[Ball_TransamMax - i]);
				DrawSprite(balltex_transam, screen_pos.x, screen_pos.y, ball_transam_W, ball_transam_H, 0, 0, 1, 1);
			}
		}

#ifdef _DEBUG
		printf_s("--Ball------------------------------\n");
		printf_s("Pos: %f, %f\n", g_Ball.pos.x, g_Ball.pos.y);
		printf_s("Speed: %f\n", g_Ball.ballspeed);
		printf_s("VecSpeed: %f, %f\n", g_Ball.Speed.x, g_Ball.Speed.y);
		printf_s("------------------------------------\n\n");
#endif // _DEBUG
		D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Ball.pos);
		DrawSpriteColorRotate(balltex, screen_pos.x, screen_pos.y, ballW, ballH,
			0, 0, 1, 1, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), ball_Rotate);
	}
}

BALL* getBall(void)
{
	return &g_Ball;
}

BALL_HIT_OBJ* getObj_Ball(int num) {
	return &b_Obj[num];
}

void setBall(D3DXVECTOR2 POS, D3DXVECTOR2 SPEED) {
	g_Ball.pos = POS;
	g_Ball.Speed = SPEED;

	g_Ball.use = true;
}


int setObj_Ball(D3DXVECTOR2 position, D3DXVECTOR2 size, bool useBuffer, bool Reflection) {
	for (int i = 1; i < maxObj; i++)
	{
		if (!b_Obj[i].isUse)
		{
			b_Obj[i].isUse = true;
			b_Obj[i].objPos = position;
			b_Obj[i].OldobjPos = position;
			b_Obj[i].objWidth = size.x;
			b_Obj[i].objHeight = size.y;
			b_Obj[i].usebuffer = useBuffer;
			b_Obj[i].objReflection = Reflection;
			b_Obj[i].HitBall = false;
			for (int i = 0; i < Ball_TransamMax; i++)
			{
				Ball_Transam[i] = position;
			}
			//�g���Ă�obj�ԍ����ꉞ�Ԃ�(Destroy�Ƃ��ړ�����ǂɎg���Ă�)
			return i;
			break;
		}
	}
}


void DestroyObj_Ball(int objnum) {
	b_Obj[objnum].isUse = false;
}


 void Reflection() {
	g_Ball.pos = position_buffer;
	g_Ball.Speed = speed_buffer;

	
}



//�{�[���̃X�s�[�h�������
void SlowSpeedBall(float speeddown) {
	g_Ball.Speed *= Ball_speeddown_onHit * speeddown;
}


//�{�[���e��
void Bumper(float power) {
	if (g_Ball.ballspeed <= 100)
	{
		g_Ball.Speed *= power;
	}
}

//�{�[����ɔ�΂�
void Wind_Ball(float power) {
	g_Ball.Speed.y = -g_Ball.Speed.y * Ball_speeddown_onHit * power;
}

//�l�̗͕s���Ŕ��̃��[�v����蓮�ł����w��ł��܂���ł������ǂ₟
void Warp_Ball(D3DXVECTOR2 pos) {
	g_Ball.pos = pos;
}





