
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "sound.h"
#include "Scroll.h"
#include "Background.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT  InitBackground(void);
void UninitBackground(void);
void UpdateBackground(void);
void DrawBackground(void);


int TexBackground;

D3DXVECTOR2 BG_Pos;



HRESULT  InitBackground(void) {
	BG_Pos.x = BG_WIDTH  / 2;
	BG_Pos.y = BG_HEIGHT / 2;


	TexBackground = LoadTexture("data/TEXTURE/BG_BETA.png");


	return E_NOTIMPL;
}




void UninitBackground(void) {

}



void UpdateBackground(void) {
}


void DrawBackground(void) {

	D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(BG_Pos);
	DrawSprite(TexBackground, screen_pos.x, screen_pos.y, BG_WIDTH, BG_HEIGHT, 0, 0, 1, 1);

}




