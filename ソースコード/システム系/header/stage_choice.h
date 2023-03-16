//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


enum STAGECHOICE
{
	ST1_1,
	ST1_2,
	ST1_3,
	ST1_4,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage1_1(void);
void DrawStage1_2(void);
void DrawStage1_3(void);
void DrawStage1_4(void);

void DrawStage2_1(void);
void DrawStage2_2(void);
void DrawStage2_3(void);
void DrawStage2_4(void);

void DrawStage3_1(void);
void DrawStage3_2(void);
void DrawStage3_3(void);
void DrawStage3_4(void);



