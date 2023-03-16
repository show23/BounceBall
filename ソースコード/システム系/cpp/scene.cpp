/*==============================================================================

   シーン管理 [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "game.h"
#include "GameOver.h"
#include "Clear.h"
#include "secret.h"
#include "world_choice.h"
#include "stage_choice.h"
#include "Team_LOGO.h"
#include "fade.h"


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		InitLOGO();
		break;
	
	case SCENE_TITLE:
		InitTitle();
		break;

		/*-----------------------
	   ゲーム読み込み
	-----------------------------*/

	case SCENE_GAME1_1:
		InitGame(game1_1);
		break;
	case SCENE_GAME1_2:
		InitGame(game1_2);
		break;
	case SCENE_GAME1_3:
		InitGame(game1_3);
		break;
	case SCENE_GAME1_4:
		InitGame(game1_4);
		break;
	case SCENE_GAME2_1:
		InitGame(game2_1);
		break;
	case SCENE_GAME2_2:
		InitGame(game2_2);
		break;
	case SCENE_GAME2_3:
		InitGame(game2_3);
		break;
	case SCENE_GAME2_4:
		InitGame(game2_4);
		break;
	case SCENE_GAME3_1:
		InitGame(game3_1);
		break;
	case SCENE_GAME3_2:
		InitGame(game3_2);
		break;
	case SCENE_GAME3_3:
		InitGame(game3_3);
		break;
	case SCENE_GAME3_4:
		InitGame(game3_4);
		break;

		/*-----------------------
	   クリア・リザルト
	-----------------------------*/

	
	case SCENE_GAMEOVER_cont:
		InitGameOver();
		break;

	case SCENE_GAMEOVER_selec:
		InitGameOver();
		break;

	case SCENE_GAMEOVER_exit:
		InitGameOver();
		break;


	case SCENE_CLEAR_cont:
		InitClear();
		break;
	case SCENE_CLEAR_selec:
		InitClear();
		break;
	case SCENE_CLEAR_next:
		InitClear();
		break;
	case SCENE_CLEAR_exit:
		InitClear();
		break;
		/*----------------------------
	   ワールド読み込み
    ----------------------------------*/

	case SCENE_WORLD1:
		InitWorld();
		break;
	case SCENE_WORLD2:
		InitWorld();
		break;
	case SCENE_WORLD3:
		InitWorld();
		break;
	case SCENE_WORLD4:
		InitWorld();
		break;

		/*----------------------------
	   ステージ選択
	--------------------------------*/

	case SCENE_STAGE1_1:
		InitStage();
		break;
	case SCENE_STAGE1_2:
		InitStage();
		break;
	case SCENE_STAGE1_3:
		InitStage();
		break;
	case SCENE_STAGE1_4:
		InitStage();
		break;
	case SCENE_STAGE2_1:
		InitStage();
		break;
	case SCENE_STAGE2_2:
		InitStage();
		break;
	case SCENE_STAGE2_3:
		InitStage();
		break;
	case SCENE_STAGE2_4:
		InitStage();
		break;
	case SCENE_STAGE3_1:
		InitStage();
		break;
	case SCENE_STAGE3_2:
		InitStage();
		break;
	case SCENE_STAGE3_3:
		InitStage();
		break;
	case SCENE_STAGE3_4:
		InitStage();
		break;



	case SCENE_PLAN_SECRET:
		InitSecret();
		break;
	case SCENE_PROG_SECRET:
		InitSecret();
		break;
	case SCENE_DESI_SECRET:
		InitSecret();
		break;
	}
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;


	case SCENE_LOGO:
		UninitLOGO();
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

		/*-----------------------
	   ゲーム読み込み
	-----------------------------*/
	case SCENE_GAME1_1:
		UninitGame();
		break;
	case SCENE_GAME1_2:
		UninitGame();
		break;
	case SCENE_GAME1_3:
		UninitGame();
		break;
	case SCENE_GAME1_4:
		UninitGame();
		break;
	case SCENE_GAME2_1:
		UninitGame();
		break;
	case SCENE_GAME2_2:
		UninitGame();
		break;
	case SCENE_GAME2_3:
		UninitGame();
		break;
	case SCENE_GAME2_4:
		UninitGame();
		break;
	case SCENE_GAME3_1:
		UninitGame();
		break;
	case SCENE_GAME3_2:
		UninitGame();
		break;
	case SCENE_GAME3_3:
		UninitGame();
		break;
	case SCENE_GAME3_4:
		UninitGame();
		break;


		/*-----------------------
	   クリア・リzると
	-----------------------------*/
	
	case SCENE_GAMEOVER_cont:
		UninitGameOver();
		break;

	case SCENE_GAMEOVER_selec:
		UninitGameOver();
		break;
	case SCENE_GAMEOVER_exit:
		UninitGameOver();
		break;


	case SCENE_CLEAR_cont:
		UninitClear();
		break;
	case SCENE_CLEAR_selec:
		UninitClear();
		break;
	case SCENE_CLEAR_next:
		UninitClear();
		break;
	case SCENE_CLEAR_exit:
		UninitClear();
		break;
		/*----------------------------
		   ワールド読み込み
	----------------------------------*/
	case SCENE_WORLD1:
		UninitWorld();
		break;
	case SCENE_WORLD2:
		UninitWorld();
		break;
	case SCENE_WORLD3:
		UninitWorld();
		break;
	case SCENE_WORLD4:
		UninitWorld();
		break;
	

		/*----------------------------
		   ステージ選択
		--------------------------------*/
	case SCENE_STAGE1_1:
		UninitStage();
		break;
	case SCENE_STAGE1_2:
		UninitStage();
		break;
	case SCENE_STAGE1_3:
		UninitStage();
		break;
	case SCENE_STAGE1_4:
		UninitStage();
		break;
	case SCENE_STAGE2_1:
		UninitStage();
		break;
	case SCENE_STAGE2_2:
		UninitStage();
		break;
	case SCENE_STAGE2_3:
		UninitStage();
		break;
	case SCENE_STAGE2_4:
		UninitStage();
		break;
	case SCENE_STAGE3_1:
		UninitStage();
		break;
	case SCENE_STAGE3_2:
		UninitStage();
		break;
	case SCENE_STAGE3_3:
		UninitStage();
		break;
	case SCENE_STAGE3_4:
		UninitStage();
		break;


	case SCENE_PLAN_SECRET:
		UninitSecret();
		break;
	case SCENE_PROG_SECRET:
		UninitSecret();
		break;
	case SCENE_DESI_SECRET:
		UninitSecret();
		break;
	}
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;


	case SCENE_LOGO:
		UpdateLOGO();
		break;


	case SCENE_TITLE:
		UpdateTitle();
		break;


		/*-----------------------
	   ゲーム読み込み
	-----------------------------*/
	case SCENE_GAME1_1:
		UpdateGame();
		break;
	case SCENE_GAME1_2:
		UpdateGame();
		break;
	case SCENE_GAME1_3:
		UpdateGame();
		break;
	case SCENE_GAME1_4:
		UpdateGame();
		break;
	case SCENE_GAME2_1:
		UpdateGame();
		break;
	case SCENE_GAME2_2:
		UpdateGame();
		break;
	case SCENE_GAME2_3:
		UpdateGame();
		break;
	case SCENE_GAME2_4:
		UpdateGame();
		break;
	case SCENE_GAME3_1:
		UpdateGame();
		break;
	case SCENE_GAME3_2:
		UpdateGame();
		break;
	case SCENE_GAME3_3:
		UpdateGame();
		break;
	case SCENE_GAME3_4:
		UpdateGame();
		break;



		/*-----------------------
		  クリア・リザルト
	   -----------------------------*/
	
	case SCENE_GAMEOVER_cont:
		UpdateGameOver();
		break;

	case SCENE_GAMEOVER_selec:
		UpdateGameOver();
		break;
	case SCENE_GAMEOVER_exit:
		UpdateGameOver();
		break;


	case SCENE_CLEAR_cont:
		UpdateClear();
		break;
	case SCENE_CLEAR_selec:
		UpdateClear();
		break;
	case SCENE_CLEAR_next:
		UpdateClear();
		break;
	case SCENE_CLEAR_exit:
		UpdateClear();
		break;
		/*----------------------------
		   ワールド読み込み
	----------------------------------*/

	case SCENE_WORLD1:
		UpdateWorld();
		break;
	case SCENE_WORLD2:
		UpdateWorld();
		break;
	case SCENE_WORLD3:
		UpdateWorld();
		break;
	case SCENE_WORLD4:
		UpdateWorld();
		break;

		/*----------------------------
		   ステージ選択
		--------------------------------*/
	case SCENE_STAGE1_1:
		UpdateStage();
		break;
	case SCENE_STAGE1_2:
		UpdateStage();
		break;
	case SCENE_STAGE1_3:
		UpdateStage();
		break;
	case SCENE_STAGE1_4:
		UpdateStage();
		break;
	case SCENE_STAGE2_1:
		UpdateStage();
		break;
	case SCENE_STAGE2_2:
		UpdateStage();
		break;
	case SCENE_STAGE2_3:
		UpdateStage();
		break;
	case SCENE_STAGE2_4:
		UpdateStage();
		break;
	case SCENE_STAGE3_1:
		UpdateStage();
		break;
	case SCENE_STAGE3_2:
		UpdateStage();
		break;
	case SCENE_STAGE3_3:
		UpdateStage();
		break;
	case SCENE_STAGE3_4:
		UpdateStage();
		break;



	case SCENE_PLAN_SECRET:
		UpdateSecret();
		break;
	case SCENE_PROG_SECRET:
		UpdateSecret();
		break;
	case SCENE_DESI_SECRET:
		UpdateSecret();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		DrawLOGO();
		break;

	case SCENE_TITLE:
		DrawTitle();
		break;


		/*-----------------------
	   ゲーム読み込み
	-----------------------------*/
	case SCENE_GAME1_1:
		DrawGame();
		break;
	case SCENE_GAME1_2:
		DrawGame();
		break;
	case SCENE_GAME1_3:
		DrawGame();
		break;
	case SCENE_GAME1_4:
		DrawGame();
		break;
	case SCENE_GAME2_1:
		DrawGame();
		break;
	case SCENE_GAME2_2:
		DrawGame();
		break;
	case SCENE_GAME2_3:
		DrawGame();
		break;
	case SCENE_GAME2_4:
		DrawGame();
		break;
	case SCENE_GAME3_1:
		DrawGame();
		break;
	case SCENE_GAME3_2:
		DrawGame();
		break;
	case SCENE_GAME3_3:
		DrawGame();
		break;
	case SCENE_GAME3_4:
		DrawGame();
		break;



		/*-----------------------
		   クリア・リザルト
		-----------------------------*/
	
	case SCENE_GAMEOVER_cont:
		DrawGameOver_cont();
		break;

	case SCENE_GAMEOVER_selec:
		DrawGameOver_selec();
		break;
	case SCENE_GAMEOVER_exit:
		DrawGameOver_exit();
		break;


	case SCENE_CLEAR_cont:
		DrawClear_cont();
		break;
	case SCENE_CLEAR_selec:
		DrawClear_selec();
		break;
	case SCENE_CLEAR_next:
		DrawClear_next();
		break;
	case SCENE_CLEAR_exit:
		DrawClear_exit();
		break;
		/*----------------------------
			   ワールド読み込み
		----------------------------------*/
	case SCENE_WORLD1:
		DrawWorld1();
		break;
	case SCENE_WORLD2:
		DrawWorld2();
		break;
	case SCENE_WORLD3:
		DrawWorld3();
		break;
	case SCENE_WORLD4:
		DrawWorld4();
		break;
	
		/*----------------------------
		   ステージ選択
		--------------------------------*/
	case SCENE_STAGE1_1:
		DrawStage1_1();
		break;
	case SCENE_STAGE1_2:
		DrawStage1_2();
		break;
	case SCENE_STAGE1_3:
		DrawStage1_3();
		break;
	case SCENE_STAGE1_4:
		DrawStage1_4();
		break;
	case SCENE_STAGE2_1:
		DrawStage2_1();
		break;
	case SCENE_STAGE2_2:
		DrawStage2_2();
		break;
	case SCENE_STAGE2_3:
		DrawStage2_3();
		break;
	case SCENE_STAGE2_4:
		DrawStage2_4();
		break;
	case SCENE_STAGE3_1:
		DrawStage3_1();
		break;
	case SCENE_STAGE3_2:
		DrawStage3_2();
		break;
	case SCENE_STAGE3_3:
		DrawStage3_3();
		break;
	case SCENE_STAGE3_4:
		DrawStage3_4();
		break;



	case SCENE_PLAN_SECRET:
		DrawPlannerSecret();
		break;
	case SCENE_PROG_SECRET:
		DrawProgrammerSecret();
		break;
	case SCENE_DESI_SECRET:
		DrawDesignerSecret();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   シーン遷移を要求する関数
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//遷移先シーンを設定する
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   遷移を要求がある場合にシーンを切り替える関数
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//現在のシーンと遷移先シーンが違っていたら
	if (g_SceneIndex != g_SceneNextIndex)
	{
		//現在のシーンを終了させる
		UninitScene();

		//遷移先シーンの初期化処理を行う
		InitScene(g_SceneNextIndex);
	}
}
