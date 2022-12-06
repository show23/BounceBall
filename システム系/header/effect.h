#ifndef _EFFECT_H_
#define _EFFECT_H_

//マクロ定義
#define MAX_EFFECT 100

//実態の情報構造体
typedef struct
{
	D3DXVECTOR2 pos;
	float size;
	bool isUse;

	int flame;
}EFFECT;

void InitEffect();
void UninitEffect();
void UpdateEffect();
void DrawEffect();
EFFECT* GetEffect();
void SetEffect(D3DXVECTOR2 pos, float size);
void AllClear_Effect();
#endif //_EFFECT_H_

