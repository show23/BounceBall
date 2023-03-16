

//�C���N���[�h
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "sound.h"
#include <time.h>
#include "Scroll.h"
#include "timer.h"
#include "fade.h"


//�O���[�o���ϐ��錾
PLAYER g_Player;

PLAYER_HIT_OBJ p_Obj[maxObj];


static int playertex;
static int playerIdleTex;
static int playerRunTex;
static int playerJumpTex;
static int playerKickTex;
static int playerDashTex;
static int playerHitTex;

static int HPberTex1;
static int HPberTex2;

int TimerFlame;
int TexSpeed;
//����
int PlayerVel;
//x������~��
float player_XMASATU = 0.15f;

//�d�͉����x
float PlayerGravity = 0.4f;


//�v���C���[�������ړ����x
float PlayerXspeed = 0.6f;

//�W�����v�͂��c�ł����˂��c
float PlayerJumpPower = 15.0f;

//�L�b�N��
//�Ȃ񂩃L�[�{�[�h�ł��ƃp�b�h�œ��͂�������苭���Ȃ�
float KickPower = 20.0f;

//�_�b�V����
float Playerdashspeed = 2.3f;


//���ɃV���b���ē�����̉����x(�����������̉����x�ő�l�ɐ��䂳��܂�)
float Player_sita_syun_naruyatu = 1.0f;

//�d�͉����x�ő�l
float P_AccYmax = 10.0f;

//���[�v�̊Ԋu
float P_Warp = 3.0f * 60;


//�v���C���[�ړ��̃X�e�B�b�N����̒l�̒����l
float stick_move_multiply = 0.001f;

//�󒆈ړ����̈ړ����x�ቺ�{��(1~0)
float playermoveMultiply_fly = 0.2f;

//�΃o�O���N�����l�p���ړ��X�s�[�h�̐���
float playerspeedmaxX = 10;


//��Ƃ��ďo����
//�L�b�N���̊p�x
float angle = 60.0f;//�x���ł̊p�x



//�R���g���[���[����Ƃ��Ă����X�e�B�b�N�������锠
//���������ƌ����������@����
//�E�R���g���[���[:-32768 �` 32768
//���X�e�B�b�N: -1000 �` 1000
//�̒l�ŕԂ��Ă���

int p_stickL_X;
int p_stickL_Y;


//�X�N���[���̊֌W�Ńv���C���[�̓������~����Ƃ�
bool moveStop;

//���[���h���W
int p_WorldX;
int p_WorldY;


//xinput�ɕύX�������A�X�e�B�b�N�̒l�����������ƂɂȂ����̂Œ����p
float xinput_adjust = 0.05f;

//�t���[�����Ƃ̏����n�Ɏg�����
float player_walptimer;
float g_U;
int g_AnimePattern;
int g_AnimeSkipFrame;
bool Jumpflag;
bool Kickflag;
bool Dashflag;
bool Damageflag;


int OldHP;


#ifdef _DEBUG
bool HitBall;
#endif // _DEBUG

bool Kicktrigger;

///////////////////////////////////
//���ʉ���`
///////////////////////////////////
unsigned static int SE_jump;
unsigned static int SE_kick;
unsigned static int SE_kick_Hit;
unsigned static int SE_warp;
unsigned static int SE_hit;


void ResetAnimePattern();
void KickBall(float radian, bool space);
void ResetSpeedPlayer();
float VecMath(int x, int y);
void PlayerWarp(void);
HRESULT InitPlayer(void)
{

	SE_jump = LoadSound("data/SE/�W�����v.wav");
	SetVolume(SE_jump, 1.0f);
	SE_kick_Hit = LoadSound("data/SE/���L�b�N.wav");
	SetVolume(SE_kick_Hit, 1.0f);
	SE_kick = LoadSound("data/SE/�p���`�̑f�U��1.wav");
	SetVolume(SE_kick, 1.0f);

	SE_warp = LoadSound("data/SE/�����ړ�.wav");
	SetVolume(SE_warp, 1.0f);
	SE_hit = LoadSound("data/SE/�|���.wav");
	SetVolume(SE_hit, 1.0f);

	playerIdleTex = LoadTexture("data/TEXTURE/IdleRight256.png");
	playerRunTex =  LoadTexture("data/TEXTURE/RunRight256.png");
	playerJumpTex = LoadTexture("data/TEXTURE/JumpRight256.png");
	playerKickTex = LoadTexture("data/TEXTURE/KickRight256.png");
	playerDashTex = LoadTexture("data/TEXTURE/DashRight256.png");
	playerHitTex = LoadTexture("data/TEXTURE/damage.png");

	HPberTex1 = LoadTexture("data/TEXTURE/HP.png");
	HPberTex2 = LoadTexture("data/TEXTURE/HP_damage.png");

	//������
	g_Player.pos.x = 0;
	g_Player.pos.y = 0;
	g_Player.Speed.x = 0;
	g_Player.Speed.y = 0;
	g_Player.Hp = 5;
	player_walptimer = 0;
	PlayerVel = 1;
	TimerFlame = 0;
	g_Player.onGround = false;
	playertex = playerIdleTex;

	Jumpflag = false;
	Kickflag = false;
	Dashflag = false;
	moveStop = false;
	Kicktrigger = false;
	TexSpeed = 2;
	for (int i = 0; i < maxObj; i++)
	{
		p_Obj[i].isUse = false;
		p_Obj[i].HitPlayer = false;
		p_Obj[i].trigger = false;
	}



	return E_NOTIMPL;
}

void UninitPlayer(void)
{


}

void UpdatePlayer(void)
{

	TimerFlame++;
	if (TimerFlame > 60) {
		TimerFlame = 0;
		AddTimer(-1);
	}

	if (g_Player.use)
	{


		g_U = 0.125f * g_AnimePattern;

		g_AnimeSkipFrame++;

		if (g_AnimeSkipFrame > TexSpeed)
		{
			g_AnimePattern++;
			g_AnimeSkipFrame = 0;

			if (g_AnimePattern > 7)
				g_AnimePattern = 0;
		}


		p_stickL_X = GetGamePadState()->Gamepad.sThumbLX * xinput_adjust;
		p_stickL_Y = -1 * GetGamePadState()->Gamepad.sThumbLY * xinput_adjust;



		//--------------------------
		//�c�����ړ�
		//--------------------------


		//�����W�����v(�c�����X�N���[���̃f�o�b�O�p)
#ifdef _INFJUMP
		g_Player.onGround = true;
#endif




		//�W�����v
		if (g_Player.onGround) {
			if (
#ifdef _DEBUG				
				GetKeyboardTrigger(DIK_UP) ||
#endif // _DEBUG	
				GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_B
				)
			{
				PlaySound(SE_jump, false);
				g_Player.Speed.y = -PlayerJumpPower;
				g_Player.onGround = false;
			}
		}



		//���ɃV�������� �Ȃ���
#ifdef _DEBUG
		if (GetKeyboardPress(DIK_DOWN))
		{
			g_Player.Speed.y += Player_sita_syun_naruyatu;
		}
#endif


		if (p_stickL_Y > 700)
		{
			g_Player.Speed.y += Player_sita_syun_naruyatu;
		}


		//�������x�̐���(��C��R�I�ȓz)
		if (g_Player.Speed.y <= P_AccYmax) {

			g_Player.Speed.y += PlayerGravity;
		}



		//--------------------------
		//�������ړ�
		//--------------------------

		float Dash = 1.0f;//����v�Z�p
		float multiply_fly = 1.0f;//�W�����v���ɒx���Ȃ�z�Ɏg������(������)



		if (g_Player.onGround)
		{
			//�n�ʂɂ���Ƃ������_�b�V���ł���
			if (GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				Dash = Playerdashspeed;
			}
		}
		else
		{
			//�󒆂̉����ʐ���
			multiply_fly = playermoveMultiply_fly;
		}




#ifdef _DEBUG
		if (GetKeyboardPress(DIK_LSHIFT)) {
			Dash = Playerdashspeed;
		}

		if (GetKeyboardPress(DIK_LEFT))
		{
			g_Player.Speed.x -= (PlayerXspeed * multiply_fly) * Dash;
			playertex = playerRunTex;
			PlayerVel = -1;
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_Player.Speed.x += PlayerXspeed * Dash * multiply_fly;
			playertex = playerRunTex;
			PlayerVel = 1;
		}
#endif


		//L�{�^���Œ�~
		if (!(GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			//�X�e�B�b�N�ړ�
			g_Player.Speed.x += PlayerXspeed * Dash * multiply_fly * p_stickL_X * stick_move_multiply;
			if (fabsf(p_stickL_X) >= 0.1f) {
				playertex = playerRunTex;
				if (p_stickL_X >= 0.0f) {
					PlayerVel = 1;
				}
				else
				{
					PlayerVel = -1;
				}
			}
		}

		//���[�v�n�̏���
		if (player_walptimer < P_Warp) {
			player_walptimer++;
		}
		else {
			if (GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_X) {
				ResetAnimePattern();
				/*PlayerWarp();*/
				if (Dashflag == false)
				{
					Dashflag = true;
				}
			}

		}

		if (Dashflag == true)
		{
			TexSpeed = 1;
			playertex = playerDashTex;
			if (g_AnimePattern == 4)
			{
				PlayerWarp();
				PlaySound(SE_warp, 0);
			}
			if (g_AnimePattern == 7)
			{
				Dashflag = false;
				TexSpeed = 2;
			}
		}

		//obj�Ɠ������������̌v�Z�p�Â��ʒu���
		D3DXVECTOR2 oldpos = g_Player.pos;

		//�����x�n�̏������e���v���C���[���W�ɊҌ�
		g_Player.pos.x += g_Player.Speed.x;
		g_Player.pos.y += g_Player.Speed.y;

		//�v���C���[�̌�������(Y���W�͕ǂ�����̂ő��v���Ǝv�����ǈꉞ0�ɂ���)	
		if (g_Player.onGround)
		{
			g_Player.Speed.x
				+= player_XMASATU * -g_Player.Speed.x;
		}


		//---------------------------------
		//�{�[�����ƃ���������
		//---------------------------------

		bool playerHitOBJ_forgravityreset = false;




		//-------------------------------------
		//�I�u�W�F�N�g�H��Q���H�̂����蔻��
		//-------------------------------------
		for (int i = 1; i < maxObj; i++)
		{
			if (p_Obj[i].isUse)
			{

				p_Obj[i].HitPlayer = false;
				bool moved = false;

				if (p_Obj[i].trigger)
				{
					moved = true;
				}

				//X���Ɍ�������ꏊ������Ƃ�
				if (g_Player.pos.x + (playerW / 2) > p_Obj[i].objPos.x - (p_Obj[i].objWidth / 2) &&
					g_Player.pos.x - (playerW / 2) < p_Obj[i].objPos.x + (p_Obj[i].objWidth / 2)) {
					//Y���W���߂荞��łĂ����S��荂���ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Player.pos.y - (playerH / 2) <= p_Obj[i].objPos.y + (p_Obj[i].objHeight / 2) &&
						oldpos.y - (playerH / 2) >= p_Obj[i].OldobjPos.y + (p_Obj[i].objHeight / 2))
					{
						if (!moved) {
							g_Player.pos.y = p_Obj[i].objPos.y + ((p_Obj[i].objHeight + playerH) / 2);
							g_Player.Speed.y = PlayerGravity;
							moved = true;
						}
						p_Obj[i].HitPlayer = true;
					}


					//Y���W���߂荞��łĂ����S���Ⴂ�ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Player.pos.y + (playerH / 2) >= p_Obj[i].objPos.y - (p_Obj[i].objHeight / 2) &&
						oldpos.y + (playerH / 2) <= p_Obj[i].OldobjPos.y - (p_Obj[i].objHeight / 2))
					{
						if (!moved) {
							g_Player.pos.y = p_Obj[i].objPos.y - ((p_Obj[i].objHeight + playerH) / 2);
							g_Player.Speed.y = PlayerGravity;
							moved = true;
							playerHitOBJ_forgravityreset = true;
							g_Player.onGround = true;
						}

						p_Obj[i].HitPlayer = true;
					}
				}



				//Y���Ɍ�������ꏊ������Ƃ�
				if (g_Player.pos.y + (playerH / 2) > p_Obj[i].objPos.y - (p_Obj[i].objHeight / 2) &&
					g_Player.pos.y - (playerH / 2) < p_Obj[i].objPos.y + (p_Obj[i].objHeight / 2)) {

					//X���W���߂荞��łĂ����S��荂���ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Player.pos.x - (playerW / 2) <= p_Obj[i].objPos.x + (p_Obj[i].objWidth / 2) &&
						oldpos.x - (playerW / 2) >= p_Obj[i].OldobjPos.x + (p_Obj[i].objWidth / 2))
					{
						if (!moved) {
							g_Player.pos.x = p_Obj[i].objPos.x + ((p_Obj[i].objWidth + playerW) / 2);
							g_Player.Speed.x = 0;
							moved = true;
						}
						p_Obj[i].HitPlayer = true;

					}


					//X���W���߂荞��łĂ����S���Ⴂ�ʒu�ɂ߂荞�ݓ_������Ƃ�
					if (g_Player.pos.x + (playerW / 2) >= p_Obj[i].objPos.x - (p_Obj[i].objWidth / 2) &&
						oldpos.x + (playerW / 2) <= p_Obj[i].OldobjPos.x - (p_Obj[i].objWidth / 2))
					{
						if (!moved) {
							g_Player.pos.x = p_Obj[i].objPos.x - ((p_Obj[i].objWidth + playerW) / 2);
							g_Player.Speed.x = 0;
							moved = true;
						}
						p_Obj[i].HitPlayer = true;
					}
				}
			}

			p_Obj[i].OldobjPos = p_Obj[i].objPos;

		}

		//�n�ʂɂ������Ă�Ƃ��͑��x�[��
		if (playerHitOBJ_forgravityreset)
		{
			g_Player.Speed.y = 0;
		}




		if (fabsf(g_Player.Speed.x) >= playerspeedmaxX)
		{
			if (g_Player.Speed.x > 0)
			{
				g_Player.Speed.x = playerspeedmaxX;
			}
			else {
				g_Player.Speed.x = -playerspeedmaxX;
			}
		}

		//SetPlayerTexture();
		if (g_Player.Speed.x < 1.0 && g_Player.Speed.x > -1.0 && Dashflag == false)
		{
			playertex = playerIdleTex;
		}


		if (Kickflag == false)
		{
			if (g_Player.Speed.y < 0 && g_Player.onGround == false)
			{
				if (Jumpflag == false)
				{
					g_AnimePattern = 0;
					Jumpflag = true;
				}

				playertex = playerJumpTex;

				if (g_AnimePattern > 2)
				{
					g_AnimePattern = 2;
				}
			}
			if (g_Player.Speed.y >= 0 && g_Player.onGround == false)
			{
				playertex = playerJumpTex;
				if (g_AnimePattern < 4 || g_Player.onGround == false)
				{
					Jumpflag = false;
					g_AnimePattern = 6;
				}
			}
		}

		if ( //�L�b�N�̃{�^���ɂ��Ă̏���
#ifdef _DEBUG
			GetKeyboardTrigger(DIK_SPACE) ||
#endif
			GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{

			if (!Kicktrigger) {
				ResetAnimePattern();
				if (Kickflag == false)
				{
					Kickflag = true;
				}
			}

			Kicktrigger = true;
		}
		else {
			Kicktrigger = false;
		}

		if (Kickflag == true)//�L�b�N�̏���
		{
			TexSpeed = 1;
			playertex = playerKickTex;
			if (g_AnimePattern == 2)
			{
				int adjust = 6;

				BALL& ball = *getBall();
				if (ball.pos.x + (ballW / 2) >= g_Player.pos.x - (playerW / 2 + adjust) &&
					ball.pos.x - (ballW / 2) <= g_Player.pos.x + (playerW / 2 + adjust) &&
					ball.pos.y + (ballH / 2) >= g_Player.pos.y - (playerH / 2 + adjust) &&
					ball.pos.y - (ballH / 2) <= g_Player.pos.y + (playerH / 2 + adjust))
				{
					PlaySound(SE_kick_Hit, false);
					KickBall(VecMath(p_stickL_X, p_stickL_Y), false);
				}
				else
				{
					PlaySound(SE_kick, false);
				}

			}

			if (g_AnimePattern == 7)
			{
				Kickflag = false;
				TexSpeed = 2;
			}
		}



		//�_���[�W�󂯂����ɃJ�����h�炷�@�\
		if (g_Player.Hp != OldHP)
		{
			CameraMove(20);
			PlaySound(SE_hit, 0);
		}

		if (Damageflag == true)
		{
			playertex = playerHitTex;
			if (g_AnimePattern == 7)
			{
				Damageflag = false;
			}
		}


		OldHP = g_Player.Hp;

		if (g_Player.Hp <= 0) {
			SetOldScene(); 
			VolumeLow();
			SceneTransition(SCENE_GAMEOVER_cont);
		}

	}

}



void ResetSpeedPlayer() {
	g_Player.Speed.x = 0;
	g_Player.Speed.y = 0;
}

void DrawPlayer(void)
{
	if (g_Player.use)
	{

#ifdef _DEBUG
		printf_s("--PLAYER----------------------------\n");
		printf_s("Pos: %f, %f\n", g_Player.pos.x, g_Player.pos.y);
		printf_s("VecSpeed: %f, %f\n", g_Player.Speed.x, g_Player.Speed.y);
		printf_s("OnGround: %s\n", (g_Player.onGround ? "true " : "false"));
		printf_s("Hit_Ball: %s\n", (HitBall ? "true " : "false"));
		printf_s("HP: %d\n", g_Player.Hp);
		printf_s("------------------------------------\n\n");
#endif // _DEBUG

		//�`�揈���̂����}������(�K�X�Ή�)
		int Y_zure = ((playerHD - playerH) / 2) - 4;


		D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Player.pos);

		DrawSprite(playertex, screen_pos.x, screen_pos.y - Y_zure, playerWD, playerHD, g_U, 1, 0.125f * PlayerVel, 1);

		int bersize = 38;
		int HPBerPOSX = 40;
		int HPBerPOSY = 25;


		for (int i = 0; i < 5; i++)
		{
			int tex = HPberTex2;
			if (g_Player.Hp > i) {
				tex = HPberTex1;
			}
			DrawSprite(tex, HPBerPOSX + (bersize * i), HPBerPOSY, bersize, bersize,0,0,1,1);
		}
	}
}


void PlayerWarp(void)
{
	player_walptimer = 0;
	g_Player.pos = getBall()->pos;
	float adjust = 35.0f;//���傢��Ƀ��[�v������
	g_Player.pos.y -= adjust;
	ResetSpeedPlayer();
}

void KickBall(float radian,bool space) {
	BALL& ball = *getBall();
	if (space) {
		//�X�y�[�X�L�[�̕��̏���
#ifdef _DEBUG
		HitBall = true;
		if (GetKeyboardPress(DIK_SPACE)) {
			float radian = angle * (M_PI / 180);//�v�Z�p�Ƀ��W�A���ɕϊ�
			ball.Speed.x = sinf(radian) * (KickPower + ball.ballspeed);
			ball.Speed.y = cosf(radian) * (KickPower + ball.ballspeed);
		}
#endif // _DEBUG
	}
	else
	{   //�R���g���[���[�̕��̏���

		int tx = 1;
		int ty = 1;

		if (sinf(radian) < 0) tx = -1;
		if (cosf(radian) < 0) ty = -1;

		ball.Speed.x = (tx * fabsf(ball.Speed.x)) + (sinf(radian) * KickPower);
		ball.Speed.y = -1 * ((ty * fabsf(ball.Speed.y)) + (cosf(radian) * KickPower));
		Kicktrigger = true;
	}
}



PLAYER* getPlayer(void) 
{
	return &g_Player;
}


void AddPlayerHp(int Hp)
{
	g_Player.Hp += Hp;
	if (Hp < 0) Damageflag = true;
	setPlayerSpeed(-50, 5);
}

void setPlayer(D3DXVECTOR2 POS,D3DXVECTOR2 SPEED) {
	g_Player.pos = POS;
	g_Player.Speed = SPEED;

	g_Player.Hp = 5;
	g_Player.use = true;
	g_Player.onGround = false;

	moveStop = false;
}



float VecMath(int x,int y) {
	float r = atan2(y - 0, x - 0);
	if (r < 0) {
		r = r + 2 * M_PI;
	}
	return M_PI / 2 + r;
};



PLAYER_HIT_OBJ* getObj_Player(int num) {
	return &p_Obj[num];
}



int setObj_Player(D3DXVECTOR2 position, D3DXVECTOR2 size, bool trigger) {
	for (int i = 1; i < maxObj; i++)
	{
		if (!p_Obj[i].isUse)
		{
			p_Obj[i].isUse = true;
			p_Obj[i].objPos = position;
			p_Obj[i].OldobjPos = position;
			p_Obj[i].objWidth = size.x;
			p_Obj[i].objHeight = size.y;
			
			p_Obj[i].HitPlayer = false;

			p_Obj[i].trigger = trigger; //�������Ă��锻�肾����肽���Ƃ��p

			//�g���Ă�obj�ԍ����ꉞ�Ԃ�(Destroy�Ƃ��ړ�����ǂɎg���Ă�)
			return i;
			break;
		}
	}
}

void UpdateObj_Player(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size) {
		p_Obj[ObjectID].objPos = position;
		p_Obj[ObjectID].objWidth = size.x;
		p_Obj[ObjectID].objHeight = size.y;
		//�g���Ă�obj�ԍ����ꉞ�Ԃ�(Destroy�Ƃ��ړ�����ǂɎg���Ă�)
		return;
}



void DestroyObj_Player(int objnum) {
	p_Obj[objnum].isUse = false;
}




//�������ɂȂ�
void Slow_Player()
{
	g_Player.Speed.y = g_Player.Speed.y * 0.3;
	g_Player.Speed.x = g_Player.Speed.x * 0.3;
}


//���[�v
void Warp_Player(D3DXVECTOR2 pos)
{
	g_Player.pos = pos;
}



void setPlayerSpeed(float x, float y) {
	g_Player.Speed.x = x;
	g_Player.Speed.y = y;
}

void setPlayerOnGround(bool OnGround)
{
	g_Player.onGround = OnGround;
}

void PlayerKickAnimation(bool KickFlag)
{
	playertex = playerKickTex;
	if (KickFlag == true)
		g_AnimePattern = 0;
	KickFlag = false;
	if (g_AnimePattern == 8)
	{
		playertex = playerIdleTex;
	}
}



void ResetAnimePattern(void)
{
	g_AnimePattern = 0;
}

