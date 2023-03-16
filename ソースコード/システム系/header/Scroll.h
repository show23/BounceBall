#pragma once

#include "main.h"
#include "renderer.h"


#define WORLD_WIDTH		7288
#define WORLD_HEIGHT	725


void UpdateCamera(D3DXVECTOR2 new_pos);
D3DXVECTOR2 ConvertPositionWorldToScreen(D3DXVECTOR2 pos);


void CameraMove(int power);
D3DXVECTOR2 getWorldPos();

