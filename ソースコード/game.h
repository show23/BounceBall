#pragma once

enum GAME
{
	gameNON,
	game1_1,
	game1_2,
	game1_3,
	game1_4,
	game2_1,
	game2_2,
	game2_3,
	game2_4,
	game3_1,
	game3_2,
	game3_3,
	game3_4
};
//1�}�b�v�S�̂̍ő��Q����
//�v���C���[�A�{�[���̓����蔻���炢�낢��ȂƂ��Ŏg���Ă�̂ł߂�����厖
#define maxObj 1000


void InitGame(GAME index);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);


void VolumeLow();