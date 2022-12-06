

//インクルード
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


//グローバル変数宣言
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
//向き
int PlayerVel;
//x方向停止力
float player_XMASATU = 0.15f;

//重力加速度
float PlayerGravity = 0.4f;


//プレイヤー横方向移動速度
float PlayerXspeed = 0.6f;

//ジャンプ力ぅ…ですかねぇ…
float PlayerJumpPower = 15.0f;

//キック力
//なんかキーボードでやるとパッドで入力した時より強くなる
float KickPower = 20.0f;

//ダッシュ力
float Playerdashspeed = 2.3f;


//下にシュッって動くやつの加速度(こっちも下の加速度最大値に制御されます)
float Player_sita_syun_naruyatu = 1.0f;

//重力加速度最大値
float P_AccYmax = 10.0f;

//ワープの間隔
float P_Warp = 3.0f * 60;


//プレイヤー移動のスティック動作の値の調整値
float stick_move_multiply = 0.001f;

//空中移動時の移動速度低下倍率(1~0)
float playermoveMultiply_fly = 0.2f;

//対バグを起こす人用横移動スピードの制限
float playerspeedmaxX = 10;


//例として出した
//キック時の角度
float angle = 60.0f;//度数での角度



//コントローラーからとってきたスティック情報を入れる箱
//多分もっと効率いい方法ある
//右コントローラー:-32768 ～ 32768
//左スティック: -1000 ～ 1000
//の値で返してくる

int p_stickL_X;
int p_stickL_Y;


//スクロールの関係でプレイヤーの動きを停止するとき
bool moveStop;

//ワールド座標
int p_WorldX;
int p_WorldY;


//xinputに変更した時、スティックの値がすごいことになったので調整用
float xinput_adjust = 0.05f;

//フレームごとの処理系に使うやつら
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
//効果音定義
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

	SE_jump = LoadSound("data/SE/ジャンプ.wav");
	SetVolume(SE_jump, 1.0f);
	SE_kick_Hit = LoadSound("data/SE/小キック.wav");
	SetVolume(SE_kick_Hit, 1.0f);
	SE_kick = LoadSound("data/SE/パンチの素振り1.wav");
	SetVolume(SE_kick, 1.0f);

	SE_warp = LoadSound("data/SE/高速移動.wav");
	SetVolume(SE_warp, 1.0f);
	SE_hit = LoadSound("data/SE/倒れる.wav");
	SetVolume(SE_hit, 1.0f);

	playerIdleTex = LoadTexture("data/TEXTURE/IdleRight256.png");
	playerRunTex =  LoadTexture("data/TEXTURE/RunRight256.png");
	playerJumpTex = LoadTexture("data/TEXTURE/JumpRight256.png");
	playerKickTex = LoadTexture("data/TEXTURE/KickRight256.png");
	playerDashTex = LoadTexture("data/TEXTURE/DashRight256.png");
	playerHitTex = LoadTexture("data/TEXTURE/damage.png");

	HPberTex1 = LoadTexture("data/TEXTURE/HP.png");
	HPberTex2 = LoadTexture("data/TEXTURE/HP_damage.png");

	//初期化
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
		//縦方向移動
		//--------------------------


		//無限ジャンプ(縦方向スクロールのデバッグ用)
#ifdef _INFJUMP
		g_Player.onGround = true;
#endif




		//ジャンプ
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



		//下にシュンって なるやつ
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


		//落下速度の制限(空気抵抗的な奴)
		if (g_Player.Speed.y <= P_AccYmax) {

			g_Player.Speed.y += PlayerGravity;
		}



		//--------------------------
		//横方向移動
		//--------------------------

		float Dash = 1.0f;//走り計算用
		float multiply_fly = 1.0f;//ジャンプ時に遅くなる奴に使う数字(未実装)



		if (g_Player.onGround)
		{
			//地面にいるときだけダッシュできる
			if (GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				Dash = Playerdashspeed;
			}
		}
		else
		{
			//空中の加速量制限
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


		//Lボタンで停止
		if (!(GetGamePadState()->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			//スティック移動
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

		//ワープ系の処理
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

		//objと当たった方向の計算用古い位置情報
		D3DXVECTOR2 oldpos = g_Player.pos;

		//加速度系の処理内容をプレイヤー座標に還元
		g_Player.pos.x += g_Player.Speed.x;
		g_Player.pos.y += g_Player.Speed.y;

		//プレイヤーの減速処理(Y座標は壁がいるので大丈夫だと思うけど一応0にする)	
		if (g_Player.onGround)
		{
			g_Player.Speed.x
				+= player_XMASATU * -g_Player.Speed.x;
		}


		//---------------------------------
		//ボールけとヴぁす処理
		//---------------------------------

		bool playerHitOBJ_forgravityreset = false;




		//-------------------------------------
		//オブジェクト？障害物？のあたり判定
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

				//X軸に交錯する場所があるとき
				if (g_Player.pos.x + (playerW / 2) > p_Obj[i].objPos.x - (p_Obj[i].objWidth / 2) &&
					g_Player.pos.x - (playerW / 2) < p_Obj[i].objPos.x + (p_Obj[i].objWidth / 2)) {
					//Y座標がめり込んでてかつ中心より高い位置にめり込み点があるとき
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


					//Y座標がめり込んでてかつ中心より低い位置にめり込み点があるとき
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



				//Y軸に交錯する場所があるとき
				if (g_Player.pos.y + (playerH / 2) > p_Obj[i].objPos.y - (p_Obj[i].objHeight / 2) &&
					g_Player.pos.y - (playerH / 2) < p_Obj[i].objPos.y + (p_Obj[i].objHeight / 2)) {

					//X座標がめり込んでてかつ中心より高い位置にめり込み点があるとき
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


					//X座標がめり込んでてかつ中心より低い位置にめり込み点があるとき
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

		//地面にあったてるときは速度ゼロ
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

		if ( //キックのボタンについての処理
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

		if (Kickflag == true)//キックの処理
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



		//ダメージ受けた時にカメラ揺らす機能
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

		//描画処理のずれを抑えるやつ(適宜対応)
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
	float adjust = 35.0f;//ちょい上にワープするやつ
	g_Player.pos.y -= adjust;
	ResetSpeedPlayer();
}

void KickBall(float radian,bool space) {
	BALL& ball = *getBall();
	if (space) {
		//スペースキーの方の処理
#ifdef _DEBUG
		HitBall = true;
		if (GetKeyboardPress(DIK_SPACE)) {
			float radian = angle * (M_PI / 180);//計算用にラジアンに変換
			ball.Speed.x = sinf(radian) * (KickPower + ball.ballspeed);
			ball.Speed.y = cosf(radian) * (KickPower + ball.ballspeed);
		}
#endif // _DEBUG
	}
	else
	{   //コントローラーの方の処理

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

			p_Obj[i].trigger = trigger; //当たっている判定だけ取りたいとき用

			//使ってるobj番号を一応返す(Destroyとか移動する壁に使ってね)
			return i;
			break;
		}
	}
}

void UpdateObj_Player(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size) {
		p_Obj[ObjectID].objPos = position;
		p_Obj[ObjectID].objWidth = size.x;
		p_Obj[ObjectID].objHeight = size.y;
		//使ってるobj番号を一応返す(Destroyとか移動する壁に使ってね)
		return;
}



void DestroyObj_Player(int objnum) {
	p_Obj[objnum].isUse = false;
}




//ゆっくりになる
void Slow_Player()
{
	g_Player.Speed.y = g_Player.Speed.y * 0.3;
	g_Player.Speed.x = g_Player.Speed.x * 0.3;
}


//ワープ
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

