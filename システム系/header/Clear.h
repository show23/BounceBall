//=============================================================================
//
// clear
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitClear(void);
void UninitClear(void);
void UpdateClear(void);
void DrawClear_cont(void);
void DrawClear_selec(void);
void DrawClear_exit(void);
void DrawClear_next(void);

void nextScene(void);
void Result();
void Evaluation(void);



