

#include "main.h"
#include "Wall.h"
#include "game.h"
#include "Player.h"
#include "Ball.h"
#include "texture.h"
#include "sprite.h"

#include "Scroll.h"


WALL g_Wall[maxObj];


bool wall_huti[WORLD_WIDTH][WORLD_HEIGHT];


int dev_walltex;
int dev_walltex2;


int wall_texture[13];

void InitWall()
{
	AllClear_Wall();


	wall_texture[0] = LoadTexture("data/TEXTURE/Block_Normal.png");


	wall_texture[1] = LoadTexture("data/TEXTURE/dev_wall_edge_1.png");
	wall_texture[2] = LoadTexture("data/TEXTURE/dev_wall_edge_2.png");
	wall_texture[3] = LoadTexture("data/TEXTURE/dev_wall_edge_3.png");
	wall_texture[4] = LoadTexture("data/TEXTURE/dev_wall_edge_4.png");

	wall_texture[5] = LoadTexture("data/TEXTURE/dev_wall_edge_5.png");
	wall_texture[6] = LoadTexture("data/TEXTURE/dev_wall_edge_6.png");
	wall_texture[7] = LoadTexture("data/TEXTURE/dev_wall_edge_7.png");
	wall_texture[8] = LoadTexture("data/TEXTURE/dev_wall_edge_8.png");


	wall_texture[9] = LoadTexture("data/TEXTURE/dev_wall_edge_9.png");
	wall_texture[10] = LoadTexture("data/TEXTURE/dev_wall_edge_10.png");
	wall_texture[11] = LoadTexture("data/TEXTURE/dev_wall_edge_11.png");
	wall_texture[12] = LoadTexture("data/TEXTURE/dev_wall_edge_12.png");


	dev_walltex2 = LoadTexture("data/TEXTURE/dev_wall.png");
	dev_walltex = LoadTexture("data/TEXTURE/Block_Normal.png");

}


void UninitWall()
{
}


void UpdateWall()
{
}


void DrawWall()
{
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wall[i].use) {
			D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(g_Wall[i].pos);
			int texture = dev_walltex;
			if (g_Wall[i].textype == 1)
			{
				texture = dev_walltex2;
			}
			DrawSprite(texture, screen_pos.x, screen_pos.y, g_Wall[i].size.x, g_Wall[i].size.y, 0, 0, 1, 1);
		}
	}

	D3DXVECTOR2 worldpos = getWorldPos();
	worldpos.x -= (SCREEN_WIDTH / 2);
	worldpos.y -= (SCREEN_HEIGHT / 2);

	for (int y = worldpos.y; y < worldpos.y + SCREEN_HEIGHT; y++)
	{
		for (int x = worldpos.x; x < worldpos.x + SCREEN_WIDTH; x++)
		{
			/*
			フチのタイプを分けるやーつ
			1~4  直線壁
			5~12 角  壁
			*/

			if (wall_huti[x][y])
			{
				int drawtype = 0;
				int conersize = 9;
				int adjust = conersize - 1;

				D3DXVECTOR2 drawpos;
				D3DXVECTOR2 drawsize = D3DXVECTOR2(conersize, conersize);

				//右壁
				if (!wall_huti[x + 1][y] &&
					wall_huti[x][y + adjust] &&
					wall_huti[x][y - adjust])
				{
					drawtype = 1;

					drawsize.x = conersize;
					drawsize.y = 1;

					drawpos.x = x - (drawsize.x / 2) + 1;
					drawpos.y = y + 1;
				}

				//左壁
				if (!wall_huti[x - 1][y] &&
					wall_huti[x][y + adjust] &&
					wall_huti[x][y - adjust])
				{
					drawtype = 2;
					drawsize.x = conersize;
					drawsize.y = 1;

					drawpos.x = x + (drawsize.x / 2);
					drawpos.y = y + 1;
				}

				//下壁
				if (!wall_huti[x][y + 1] &&
					wall_huti[x + adjust][y] &&
					wall_huti[x - adjust][y])
				{
					drawtype = 3;
					drawsize.x = 1.0f;
					drawsize.y = conersize;

					drawpos.x = x + 1;
					drawpos.y = y - (drawsize.y / 2) + 1;
				}
				//上壁
				if (!wall_huti[x][y - 1] &&
					wall_huti[x + adjust][y] &&
					wall_huti[x - adjust][y])
				{
					drawtype = 4;
					drawsize.x = 1.0f;
					drawsize.y = conersize;

					drawpos.x = x + 1;
					drawpos.y = y + (drawsize.y / 2);
				}

				

				
				//ここから先、角
				//
				//  ↓ここを検知する
				//  ■■■■■■■
				//  ■■■■■■■
				//  ■■■
				//  ■■■
				// 
				//外側？を検知する

				//右下壁
				if (!wall_huti[x + 1][y] &&
					!wall_huti[x][y + 1] &&
					!wall_huti[x + 1][y + 1])
				{
					drawsize.x = conersize;
					drawsize.y = conersize;
					drawtype = 9;
					drawpos.x = x - (drawsize.x / 2)+1;
					drawpos.y = y - (drawsize.y / 2)+1;
				}

				//左下壁
				if (!wall_huti[x - 1][y] &&
					!wall_huti[x][y + 1] &&
					!wall_huti[x - 1][y + 1])
				{
					drawsize.x = conersize;
					drawsize.y = conersize;
					drawtype = 10;
					drawpos.x = x + (drawsize.x / 2);
					drawpos.y = y - (drawsize.y / 2)+1;
				}



				//右上壁
				if (!wall_huti[x + 1][y] &&
					!wall_huti[x][y - 1] &&
					!wall_huti[x + 1][y - 1])
				{
					drawsize.x = conersize;
					drawsize.y = conersize;
					drawtype = 11;
					drawpos.x = x - (drawsize.x / 2)+1;
					drawpos.y = y + (drawsize.y / 2);
				}
				//左上壁
				if (!wall_huti[x - 1][y] &&
					!wall_huti[x][y - 1] &&
					!wall_huti[x - 1][y - 1])
				{
					drawsize.x = conersize;
					drawsize.y = conersize;
					drawtype = 12;
					drawpos.x = x + (drawsize.x / 2);
					drawpos.y = y + (drawsize.y / 2);
				}
				
				
				//■■■■
				//■■■■
				//■■┌
				//■■  ここ(内側？なんといえばいいかわからない)を検知する
				//


				//左上壁
				if (!wall_huti[x + 1][y + 1] &&
					wall_huti[x][y + 1] &&
					wall_huti[x + 1][y])
				{
					drawtype = 5;
					drawsize = D3DXVECTOR2(conersize, conersize);
					drawpos.x = x - (drawsize.x / 2)+1;
					drawpos.y = y - (drawsize.y / 2)+1;
				}
				//右上壁
				if (!wall_huti[x - 1][y + 1] &&
					wall_huti[x][y + 1] &&
					wall_huti[x - 1][y])
				{
					drawtype = 6;
					drawsize = D3DXVECTOR2(conersize, conersize);
					drawpos.x = x + (drawsize.x / 2);
					drawpos.y = y - (drawsize.y / 2)+1;
				}


				//左下壁
				if (!wall_huti[x + 1][y - 1] &&
					wall_huti[x][y - 1] &&
					wall_huti[x + 1][y])
				{
					drawtype = 7;
					drawsize = D3DXVECTOR2(conersize, conersize);
					drawpos.x = x - (drawsize.x / 2)+1;
					drawpos.y = y + (drawsize.y / 2);
				}
				//右下壁
				if (!wall_huti[x - 1][y - 1] &&
					wall_huti[x][y - 1] &&
					wall_huti[x - 1][y])
				{
					drawtype = 8;
					drawsize = D3DXVECTOR2(conersize, conersize);
					drawpos.x = x + (drawsize.x / 2);
					drawpos.y = y + (drawsize.y / 2);
				}
				

				if (drawtype != 0) {
					

					D3DXVECTOR2 screen_pos = ConvertPositionWorldToScreen(drawpos);

					//画面内の時だけ描画
					if (screen_pos.x - (drawsize.x / 2) <= SCREEN_WIDTH &&
						screen_pos.x + (drawsize.x / 2) > 0 &&
						screen_pos.y - (drawsize.y / 2) <= SCREEN_HEIGHT &&
						screen_pos.y + (drawsize.y / 2) > 0)
					{
						DrawSprite(wall_texture[drawtype], screen_pos.x, screen_pos.y, drawsize.x, drawsize.y, 0, 0, 1, 1);
					}

				}
			}
		}
	}
}


void AllClear_Wall() {
	for (int i = 0; i < maxObj; i++)
	{
		if (g_Wall[i].use)
		{
			PLAYER_HIT_OBJ* w_Pobj = getObj_Player(g_Wall[i].numObj_Player);
			BALL_HIT_OBJ* w_Bobj = getObj_Ball(g_Wall[i].numObj_Ball);
			w_Pobj->isUse = false;
			w_Bobj->isUse = false;
			g_Wall[i].use = false;
		}
	}

	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < WORLD_WIDTH; x++)
		{
			wall_huti[x][y] = false;
		}
	}

}

void setWall(D3DXVECTOR2 pos,D3DXVECTOR2 size ,int tex_type) {
	for (int i = 0; i < maxObj; i++)
	{
		if (!g_Wall[i].use)
		{
			g_Wall[i].use = true;
			
			for (int y = pos.y; y < pos.y + size.y; y++)
			{
				for (int x = pos.x; x < pos.x + size.x; x++)
				{
					wall_huti[x][y] = true;
				}
			}



			pos += size / 2;
			
			g_Wall[i].pos = pos;
			g_Wall[i].size = size;

			g_Wall[i].textype = tex_type;

			g_Wall[i].numObj_Player = setObj_Player(pos, size, false);
			g_Wall[i].numObj_Ball = setObj_Ball(pos, size, false, true);
			break;
		}
	}
}
