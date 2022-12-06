/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :Joy
														 Date   :

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Scroll.h"
#include "scene.h"
#include "effect.h"

//--------------------------------------
//	追加ヘッダー定義(忘れないでね)
//--------------------------------------



#include "Wall.h"
#include "BreakableWall.h"
#include "Slowboundwall.h"
#include "SlowField.h"
#include "AccelerationBlock.h"
#include "Bumper.h"
#include "Wind.h"
#include "WarpBox.h"
#include "SwitchWall.h"
#include "enemy.h"
#include "bullet.h"
#include "goal.h"
#include "timer.h"
#include "score.h"

//----------------------------------------------
//ステージ系のスクリプトのヘッダー
//----------------------------------------------

#include "TEST_SCENE.h"

#include "SCENE_1_1.h"
#include "SCENE_1_2.h"
#include "SCENE_1_3.h"
#include "SCENE_1_4.h"


#include "SCENE_2_1.h"
#include "SCENE_2_2.h"
#include "SCENE_2_3.h"
#include "SCENE_2_4.h"

#include "SCENE_3_1.h"
#include "SCENE_3_2.h"
#include "SCENE_3_3.h"
#include "SCENE_3_4.h"

#include"stage_choice.h"
 /*------------------------------------------------------------------------------
	定数定義
 ------------------------------------------------------------------------------*/



 /*------------------------------------------------------------------------------
	構造体宣言
 ------------------------------------------------------------------------------*/


GAME gameIndex = gameNON;
GAME oldIndex = gameNON;



 /*------------------------------------------------------------------------------
	プロトタイプ宣言
 ------------------------------------------------------------------------------*/

void Clear_OBJ();

 /*------------------------------------------------------------------------------
	グローバル変数の定義
 ------------------------------------------------------------------------------*/
unsigned int g_BGM1;
unsigned int g_BGM2;
unsigned int g_BGM3;


 /*------------------------------------------------------------------------------
	初期化関数
 ------------------------------------------------------------------------------*/
void InitGame(GAME index)
{
	gameIndex = index;

	StopSoundAll();

	InitPlayer();
	InitBall();
	InitBackground();
	InitWall();
	InitWall_B();
	InitSlowboundwall();
	InitSlowfield();
	InitBumper();
	InitWind();
	InitWarpBox();
	InitSwitch_W();
	InitAccelerationBlock();
	InitEnemy_B(); 
	InitBullet();
	InitGoal();
	InitScore();
	InitTimer();
	InitEffect();
	
	Clear_OBJ();
	g_BGM1 = LoadSound("data/BGM/Hyper_Chase.wav");
	g_BGM2 = LoadSound("data/BGM/R246_Midnight.wav");
	g_BGM3 = LoadSound("data/BGM/Techno_Trap.wav");



	SetVolume(g_BGM1, 0.2f);
	SetVolume(g_BGM2, 0.2f);
	SetVolume(g_BGM3, 0.2f);



	StopSoundAll();

	switch (gameIndex)
	{
	case game1_1:
		PlaySound(g_BGM1, -1);
		SetSCENE_1_1();
		break;
	case game1_2:
		PlaySound(g_BGM1, -1);
		SetSCENE_1_2();
		break;
	case game1_3:
		PlaySound(g_BGM1, -1);
		SetSCENE_1_3();
		break;
	case game1_4:
		PlaySound(g_BGM1, -1);
		SetSCENE_1_4();
		break;



	case game2_1:
		PlaySound(g_BGM2, -1);
		SetSCENE_2_1();
		break;
	case game2_2:
		PlaySound(g_BGM2, -1);
		SetSCENE_2_2();
		break;
	case game2_3:
		PlaySound(g_BGM2, -1);
		SetSCENE_2_3();
		break;
	case game2_4:
		PlaySound(g_BGM2, -1);
		SetSCENE_2_4();
		break;


	case game3_1:
		PlaySound(g_BGM3, -1);
		SetSCENE_3_1();
		break;
	case game3_2:
		PlaySound(g_BGM3, -1);
		SetSCENE_3_2();
		break;
	case game3_3:
		PlaySound(g_BGM3, -1);
		SetSCENE_3_3();
		break;
	case game3_4:
		PlaySound(g_BGM3, -1);
		SetSCENE_3_4();
		break;
	}

	oldIndex = gameIndex;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	UninitPlayer();
	UninitBall();
	UninitBackground();
	UninitWall();
	UninitWall_B();
	UninitSlowboundwall();
	UninitSlowfield();
	UninitBumper();
	UninitWind();
	UninitWarpBox();
	UninitSwitch_W();
	UninitAccelerationBlock();
	UninitEnemy_B();
	UninitBullet();
	UninitGoal();

	UninitEffect();

	UninitScore();
	UninitTimer();
}


/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{

	//スクロール位置更新
	UpdateCamera(getPlayer()->pos);
	
	UpdateBackground();
	UpdateWall();
	UpdateWall_B();
	UpdateSlowboundwall();
	UpdateSlowfield();
	UpdateBumper();
	UpdateWind();
	UpdateWarpBox();
	UpdateSwitch_W();
	UpdateAccelerationBlock();
	UpdateEnemy_B();
	UpdateBullet();
	UpdateGoal();

	UpdateEffect();

	UpdateScore();
	UpdateTimer();

	UpdatePlayer();
	UpdateBall();

	

}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{

	DrawBackground();
	DrawSwitch_W();
	DrawWall_B();
	DrawSlowboundwall();
	DrawSlowfield();
	DrawWarpBox();
	DrawWind();
	DrawBumper();
	DrawGoal();

	DrawAccelerationBlock();
	DrawWall();

	DrawScore();
	DrawTimer();

	DrawEffect();

	DrawEnemy_B();
	DrawBullet();

	DrawPlayer();
	DrawBall();


}


//壁等のオブジェクト系をすべて削除する関数
void Clear_OBJ() {
	AllClear_Bumper();
	AllClear_Slowboundwall();
	AllClear_Slowfield();
	AllClear_Switch();
	AllClear_Wall();
	AllClear_Wall_B();
	AllClear_Wind();
	AllClear_Enemy_B();
	AllClear_WarpBox();
	AllClear_Bullet();
	AllClear_AccelerationBlock();
	AllClear_Goal();
	AllClear_Effect();
}

void VolumeLow(){
	switch (oldIndex)
	{
	case game1_1:
		SetVolume(g_BGM1, 0.05f);
		break;
	case game1_2:
		SetVolume(g_BGM1, 0.05f);
		break;
	case game1_3:
		SetVolume(g_BGM1, 0.05f);
		break;
	case game1_4:
		SetVolume(g_BGM1, 0.05f);
		break;
	case game2_1:
		SetVolume(g_BGM2, 0.05f);
		break;
	case game2_2:
		SetVolume(g_BGM2, 0.05f);
		break;
	case game2_3:
		SetVolume(g_BGM2, 0.05f);
		break;
	case game2_4:
		SetVolume(g_BGM2, 0.05f);
		break;
	case game3_1:
		SetVolume(g_BGM3, 0.05f);
		break;
	case game3_2:
		SetVolume(g_BGM3, 0.05f);
		break;
	case game3_3:
		SetVolume(g_BGM3, 0.05f);
		break;
	case game3_4:
		SetVolume(g_BGM3, 0.05f);
		break;
	default:
		SetVolume(g_BGM1, 0.05f);
		SetVolume(g_BGM2, 0.05f);
		SetVolume(g_BGM3, 0.05f);
		break;
	}
}


