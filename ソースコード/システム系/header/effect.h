#ifndef _EFFECT_H_
#define _EFFECT_H_

//�}�N����`
#define MAX_EFFECT 100

//���Ԃ̏��\����
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

