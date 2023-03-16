#pragma once

#define TIMER_FIGURE 3 //åÖ	
#define COUNT 300 //ïbêî

void InitTimer();
void UninitTimer();
void UpdateTimer();
void DrawTimer();

void AddTimer(int Time);
void SetTimer(int Time);

void getOldTime(void);
void SetOldTime(int STimer, int ATimer, int BTimer, int CTimer);