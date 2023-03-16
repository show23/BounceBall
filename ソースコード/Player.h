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
    float pMax; // �ő�l
    float pMin; // �ŏ��l
    float pPre; // ���ݒl

public:
    
    ExNum(float max = 0, float min = 0, float pre = 0)
        :pMax(max), pMin(min), pPre(pre) {}

    float getMax() { return pMax; }
    float getMin() { return pMin; }
    float get() { return pPre; }

    // �ő�l���Z�b�g���鎞�͍ŏ��l��菬�����Ȃ�Ȃ��悤�ɂ���B
    // �܂����ݒl���ő�l�𒴂��Ă���Ȃ�A�ő�l�Ɠ����ɂ���B
    void setMax(float value)
    {
        pMax = max(pMin, value);
        if (pMax < get()) set(pMax);
    }

    // �ŏ��l���Z�b�g���鎞�͍ő�l���傫���Ȃ�Ȃ��悤�ɂ���B
    // ���ݒl���ŏ��l�����ɂȂ�Ȃ�A�ŏ��l�Ɠ����ɂ���B
    void setMin(float value)
    {
        pMin = min(value, pMax);
        if (get() < pMin) set(pMin);
    }

    // ���ݒl���Z�b�g���鎞�͍ŏ��l�ȏ�A�ő�l�ȉ��ɂȂ�悤�ɂ���B
    void set(float value)
    {
        value = min(value, pMax);
        value = max(value, pMin);
        pPre = value;

        
    }
    // ���ݒl��ǉ��A�߂�l�ōŏI�I�Ȓl��Ԃ��ƕ֗��H
    float add(float value)
    {
        set(get() + value);
        return get();
    }

    // �ő�l��ǉ�
    float addMax(float value)
    {
        setMax(getMax() + value);
        return getMax();
    }

    // �ŏ��l��ǉ�
    float addMin(float value) {
        setMin(getMin() + value);
        return getMin();
    }

    // HP����
    bool isEmpty() {
        return (get() <= getMin()); // �ŏ��l�ȉ��Ȃ�󂾂��
    }

    // HP�����^��
    bool isFull() {
        return (getMax() <= get()); // �ő�l�ȏ�Ȃ疞�^������ˁB
    }
    // �������擾
    float rate() {
        return (get() / getMax()); // ���ݒl / �ő�l
    }
};
*/
//�W�����v�����`�[�g
//#define _INFJUMP

//�v���C���[���������蔻�肪���锠
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
//�v���C���[��obj���{�[����obj���A0�Ԃ̔z��ɂ͉�������Ȃ��悤�ɂ���̂Ō��ʂƂ���0������Ɠ����蔻�肪�Ȃ��u���b�N�ɂȂ�








struct PLAYER
{
	bool					use;			// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				pos;			// �v���C���[���W
	D3DXVECTOR2				Speed;			// �v���C���[�����x

	bool					onGround;		//�n�ʂƐڐG���Ă��邩

	int						Hp;				//�v���C���[�̗̑�(����Ƃ��g�����Ȃ�)
};


//*****************************************************************************
// �v���g�^�C�v�錾
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

