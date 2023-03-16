#pragma once


#include "main.h"
#include "renderer.h"

#define BG_WIDTH 7288
#define BG_HEIGHT 720

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT  InitBackground(void);
void UninitBackground(void);
void UpdateBackground(void);
void DrawBackground(void);




