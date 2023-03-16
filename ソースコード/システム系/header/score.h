#pragma once

#define SCORE_FIGURE 4 //Œ…	

void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int Score);

void OldScore(void);
void SetOldScore(int SScore, int AScore, int BScore, int CScore);