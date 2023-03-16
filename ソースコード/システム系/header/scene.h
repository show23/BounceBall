#pragma once

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,		//シーン処理なし
	SCENE_LOGO,
	SCENE_TITLE,	//タイトル



	SCENE_GAME1_1,		//ゲーム
	SCENE_GAME1_2,
	SCENE_GAME1_3,
	SCENE_GAME1_4,
	SCENE_GAME2_1,
	SCENE_GAME2_2,
	SCENE_GAME2_3,
	SCENE_GAME2_4,
	SCENE_GAME3_1,
	SCENE_GAME3_2,
	SCENE_GAME3_3,
	SCENE_GAME3_4,
	



	//リザルト
	SCENE_RESULT,	
	SCENE_GAMEOVER_cont,
	SCENE_GAMEOVER_selec,
	SCENE_GAMEOVER_exit,


	SCENE_CLEAR,
	SCENE_CLEAR_cont,
	SCENE_CLEAR_selec,
	SCENE_CLEAR_next,
	SCENE_CLEAR_exit,

	SCENE_WORLD1,
	SCENE_WORLD2,
	SCENE_WORLD3,
	SCENE_WORLD4,

	SCENE_STAGE1_1,
	SCENE_STAGE1_2,
	SCENE_STAGE1_3,
	SCENE_STAGE1_4,
	SCENE_STAGE2_1,
	SCENE_STAGE2_2,
	SCENE_STAGE2_3,
	SCENE_STAGE2_4,
	SCENE_STAGE3_1,
	SCENE_STAGE3_2,
	SCENE_STAGE3_3,
	SCENE_STAGE3_4,


	SCENE_PLAN_SECRET,
	SCENE_PROG_SECRET,
	SCENE_DESI_SECRET,

	SCENE_MAX_STAGE		//最後だとわかる奴をいれる



	
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);
