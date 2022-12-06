#pragma once


#include "main.h"
#include "renderer.h"



#define playerH 107
#define playerW 40

#define playerHD 128
#define playerWD 128

/*
class ExNum
{
private:
    float pMax; // 最大値
    float pMin; // 最小値
    float pPre; // 現在値

public:
    
    ExNum(float max = 0, float min = 0, float pre = 0)
        :pMax(max), pMin(min), pPre(pre) {}

    float getMax() { return pMax; }
    float getMin() { return pMin; }
    float get() { return pPre; }

    // 最大値をセットする時は最小値より小さくならないようにする。
    // また現在値が最大値を超えているなら、最大値と同じにする。
    void setMax(float value)
    {
        pMax = max(pMin, value);
        if (pMax < get()) set(pMax);
    }

    // 最小値をセットする時は最大値より大きくならないようにする。
    // 現在値が最小値未満になるなら、最小値と同じにする。
    void setMin(float value)
    {
        pMin = min(value, pMax);
        if (get() < pMin) set(pMin);
    }

    // 現在値をセットする時は最小値以上、最大値以下になるようにする。
    void set(float value)
    {
        value = min(value, pMax);
        value = max(value, pMin);
        pPre = value;

        
    }
    // 現在値を追加、戻り値で最終的な値を返すと便利？
    float add(float value)
    {
        set(get() + value);
        return get();
    }

    // 最大値を追加
    float addMax(float value)
    {
        setMax(getMax() + value);
        return getMax();
    }

    // 最小値を追加
    float addMin(float value) {
        setMin(getMin() + value);
        return getMin();
    }

    // HPが空
    bool isEmpty() {
        return (get() <= getMin()); // 最小値以下なら空だよね
    }

    // HPが満タン
    bool isFull() {
        return (getMax() <= get()); // 最大値以上なら満タンだよね。
    }
    // 割合を取得
    float rate() {
        return (get() / getMax()); // 現在値 / 最大値
    }
};
*/
//ジャンプ無限チート
//#define _INFJUMP

//プレイヤー向け当たり判定が入る箱
struct PLAYER_HIT_OBJ 
{
	bool isUse;
	D3DXVECTOR2 objPos;
	D3DXVECTOR2 OldobjPos;
	float objWidth;
	float objHeight;
	
	bool trigger;

	bool HitPlayer;

};
//プレイヤーのobjもボールのobjも、0番の配列には何も入れないようにするので結果として0を入れると当たり判定がないブロックになる








struct PLAYER
{
	bool					use;			// true:使っている  false:未使用
	D3DXVECTOR2				pos;			// プレイヤー座標
	D3DXVECTOR2				Speed;			// プレイヤー加速度

	bool					onGround;		//地面と接触しているか

	int						Hp;				//プレイヤーの体力(今んとこ使い道なし)
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void ResetSpeedPlayer();
void Slow_Player();
void Warp_Player(D3DXVECTOR2 pos);

void AddPlayerHp(int Hp);
void setPlayer(D3DXVECTOR2 POS, D3DXVECTOR2 SPEED);

PLAYER* getPlayer(void);
PLAYER_HIT_OBJ* getObj_Player(int num);


void UpdateObj_Player(int ObjectID, D3DXVECTOR2 position, D3DXVECTOR2 size);

int setObj_Player(D3DXVECTOR2 position, D3DXVECTOR2 size, bool trigger);
void DestroyObj_Player(int objnum);
void setPlayerOnGround(bool OnGround);
void setPlayerSpeed(float x, float y);

