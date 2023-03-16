
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "Ball.h"
#include "sound.h"
#include "game.h"
#include "effect.h"

#include "Scroll.h"

//-----------------------------
//グローバル変数宣言
//-------------------------------

//構造体
BALL g_Ball;//ボールのオブジェクト
BALL_HIT_OBJ  b_Obj[maxObj];//ボールとの当たり判定をもつオブジェクト
//テクスチャ
int balltex;
int balltex_transam;


//残像出すよ！

bool doTransam = true;
D3DXVECTOR2 Ball_Transam[Ball_TransamMax];



//------------------------------------------------------
//変更可能定数//////なんか気になるならいじれってやつ
//------------------------------------------------------
//
float ball_Rotate = 0.0f;
//x方向停止力
float ball_XMASATU = 0.10f;

//重力加速度
float BallGravity = 0.4f;

//ボールの重力加速開始速度
float BallStartGrav = 15.0f;

//ボール反射度
float Ball_bounce = 1.0f;

//重力加速度最大値
float B_AccYmax = 10.0f;

//ボール減速(1だと完全停止すると思う 0で無減速)
float Ball_speeddown_multiply = 0.05f;

//壁等衝突時のボール減速度
float Ball_speeddown_onHit = 1;

//ボールの減速(空中)
float Ball_speeddown_Plot = 0.991f;

//壁貫通防止用の速度の最大値設定
float MaxBallSpeed = 30.0f;

//ボールの跳ねる限界速度
//なんというか、ボールの移動量をゼロとみなす時の比較に使う値
//これないとやばい
//Y座標とか細かく設定しないとずっと細かくびょんびょん跳ねる
float Ball_minBounceSpeedY = 1.2f;

//計算用のなにか
D3DXVECTOR2 position_buffer;
D3DXVECTOR2 speed_buffer;

//-----------------------------------
//なんちゃら宣言
//---------------------------------

//加速度リセット
//Unity版ではRキーのボール位置リセットの時に使ってたけど
//ボール持ちたいときとかに使えるかも

void ResetSpeedBall();

//壁に当たったときの原則の関数
void SpeedDown_Ball();


void Reflection();


HRESULT InitBall(void)
{
	balltex = LoadTexture("data/TEXTURE/ball.png");
	balltex_transam = LoadTexture("data/TEXTURE/ball_transam.png");

	//------------
	//初期化
	//------------


	//位置--------
	g_Ball.pos.x = 0;
	g_Ball.pos.y = 0;
	
	//速度--------
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


		//ボールの重力加速処理
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
		//計算用の古い位置情報
		D3DXVECTOR2 oldpos = g_Ball.pos;

		//加速度系の処理内容を座標に還元
		g_Ball.pos.x += g_Ball.Speed.x;
		g_Ball.pos.y += g_Ball.Speed.y;

		//ボール減速処理--------------------------------------------------------------
		float speedmultiply = 1;
		//プロト
		speedmultiply = Ball_speeddown_Plot;

		g_Ball.Speed = g_Ball.Speed * speedmultiply;

		//スクリーンでの反射----------------------------------------------------------
		//画面との当たり判定を取りたいのでスクリーン座標に一度変換して判定します
		D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Ball.pos);
		D3DXVECTOR2 world_pos = getWorldPos();

		//画面の右側に当たったとき
		if (screen_pos.x + (ballW / 2) > SCREEN_WIDTH)
		{
			SpeedDown_Ball();
			
			g_Ball.pos.x = (SCREEN_WIDTH - ballW) / 2 + world_pos.x;
			g_Ball.Speed.x = -g_Ball.Speed.x;
		}

		//画面の左側に当たったとき
		if (screen_pos.x - (ballW / 2) < 0)
		{
			SpeedDown_Ball();
			g_Ball.pos.x = world_pos.x + ((-SCREEN_WIDTH + ballW) / 2);
			g_Ball.Speed.x = -g_Ball.Speed.x;
		}

		//画面の下側に当たったとき
		if (screen_pos.y + (ballH / 2) > SCREEN_HEIGHT)
		{
			SpeedDown_Ball();
			g_Ball.pos.y = (SCREEN_HEIGHT - ballH) / 2 + world_pos.y;
			g_Ball.Speed.y = -g_Ball.Speed.y;

			//振動低減(こっちに移動)
			if (fabsf(g_Ball.Speed.y) < Ball_minBounceSpeedY)
			{
				g_Ball.Speed.y = 0;
			}
		}

		//画面の上側に当たったとき
		if (screen_pos.y - (ballH / 2) < 0)
		{
			SpeedDown_Ball();
			g_Ball.pos.y = world_pos.y + ((-SCREEN_HEIGHT + ballH) / 2);
			g_Ball.Speed.y = -g_Ball.Speed.y;
		}

		/////オブジェクトとの当たり判定--------------------------------------------------------------

		//バッファ
		//リフレクションがtrueでセットされているオブジェクトがあるときRefrectionを呼んだ時に反射するようになってます
		//1フレームで壁を壊し、それに反射しないという処理を入れるよう

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


				//X軸に交錯する場所があるとき
				if (g_Ball.pos.x + (ballW / 2) >= b_Obj[i].objPos.x - (b_Obj[i].objWidth / 2) &&
					g_Ball.pos.x - (ballW / 2) <= b_Obj[i].objPos.x + (b_Obj[i].objWidth / 2))
				{
					//Y座標がめり込んでてかつ中心より高い位置にめり込み点があるとき
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

					//Y座標がめり込んでてかつ中心より低い位置にめり込み点があるとき
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


				//Y軸に交錯する場所があるとき
				if (g_Ball.pos.y + (ballH / 2) >= b_Obj[i].objPos.y - (b_Obj[i].objHeight / 2) &&
					g_Ball.pos.y - (ballH / 2) <= b_Obj[i].objPos.y + (b_Obj[i].objHeight / 2))
				{
					//X座標がめり込んでてかつ中心より高い位置にめり込み点があるとき
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

					//X座標がめり込んでてかつ中心より低い位置にめり込み点があるとき
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

//ボールを特定位置にワープさせるとき等はこれを呼ばないとそのままの速度で吹っ飛んでいくので注意
void ResetSpeedBall() {
	g_Ball.Speed.x = 0;
	g_Ball.Speed.y = 0;
}

void UpdateObj_Ball(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size) {
	b_Obj[ObjectID].objPos = position;
	b_Obj[ObjectID].objWidth = size.x;
	b_Obj[ObjectID].objHeight = size.y;
	//使ってるobj番号を一応返す(Destroyとか移動する壁に使ってね)
	return;
}


//壁に当たって減速する関数
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
			//使ってるobj番号を一応返す(Destroyとか移動する壁に使ってね)
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



//ボールのスピードゆっくり
void SlowSpeedBall(float speeddown) {
	g_Ball.Speed *= Ball_speeddown_onHit * speeddown;
}


//ボール弾く
void Bumper(float power) {
	if (g_Ball.ballspeed <= 100)
	{
		g_Ball.Speed *= power;
	}
}

//ボール上に飛ばす
void Wind_Ball(float power) {
	g_Ball.Speed.y = -g_Ball.Speed.y * Ball_speeddown_onHit * power;
}

//僕の力不足で箱のワープ先を手動でしか指定できませんでした←どやぁ
void Warp_Ball(D3DXVECTOR2 pos) {
	g_Ball.pos = pos;
}





