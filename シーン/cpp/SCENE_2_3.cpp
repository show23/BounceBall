

//ヘッダー定義
#include "TEST_SCENE.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "Background.h"
#include "Scroll.h"

#include "Player.h"
#include "Ball.h"

/*--------------------------------------
    追加ヘッダー定義(忘れないでね)
 -------------------------------------*/
#include "Wall.h"
#include "BreakableWall.h"
#include "Slowboundwall.h"
#include "SlowField.h"
#include "Bumper.h"
#include "Wind.h"
#include "WarpBox.h"
#include "SwitchWall.h"
#include "AccelerationBlock.h"
#include "enemy.h"
#include "Goal.h"



void SetSCENE_2_3() {
    ////プレイヤー召喚
    setPlayer(D3DXVECTOR2(200, 600), D3DXVECTOR2(0, 0));
    ////ボール
    setBall(D3DXVECTOR2(150, 550), D3DXVECTOR2(0, 0));

    //基本ブロック
    setWall(D3DXVECTOR2(0, 669), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(60, 720), 0);
    setWall(D3DXVECTOR2(7227, 0), D3DXVECTOR2(60, 720), 0);

    setWall(D3DXVECTOR2(800, 60), D3DXVECTOR2(600, 450), 0);

    setAccelerationBlock(D3DXVECTOR2(800, 510), D3DXVECTOR2(150, 160), true, RIGHT);
    setWall_B(D3DXVECTOR2(950, 510), D3DXVECTOR2(150, 160), 0);
    setWall_B(D3DXVECTOR2(1100, 510), D3DXVECTOR2(150, 160), 0);
    setWall_B(D3DXVECTOR2(1250, 510), D3DXVECTOR2(150, 160), 0);
    
    setEnemy_B(D3DXVECTOR2(1550, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);

    //----------------------------
    setWall(D3DXVECTOR2(1700, 550), D3DXVECTOR2(800, 122), 0);

    setEnemy_B(D3DXVECTOR2(1850, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(3, 0), 80, 120);
    setEnemy_B(D3DXVECTOR2(2210, 410), D3DXVECTOR2(128, 128), D3DXVECTOR2(-3, 0), 80, 120);
    setEnemy_B(D3DXVECTOR2(2210, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 3), 80, 120);
    setEnemy_B(D3DXVECTOR2(1850, 410), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -3), 80, 120);

    setWall(D3DXVECTOR2(2500, 260), D3DXVECTOR2(300, 460), 0);
    
    setAccelerationBlock(D3DXVECTOR2(2400, 60), D3DXVECTOR2(80, 80), true, RIGHT);
    setAccelerationBlock(D3DXVECTOR2(2400, 450), D3DXVECTOR2(100, 100), true, UP);
    //----------------------------
    
    setWall(D3DXVECTOR2(2800, 260), D3DXVECTOR2(300, 100), 0);
    setWall(D3DXVECTOR2(3300, 60), D3DXVECTOR2(100, 440), 0);
    setWall(D3DXVECTOR2(3100, 480), D3DXVECTOR2(300, 70), 0);

    setSlowfield(D3DXVECTOR2(3100, 60), D3DXVECTOR2(200, 300), 0.1f);

    setSlowfield(D3DXVECTOR2(2800, 360), D3DXVECTOR2(300, 200), 0.1f);

    //----------------------------

    setAccelerationBlock(D3DXVECTOR2(3400, 260), D3DXVECTOR2(150, 150), true, DOWN);
    setEnemy_B(D3DXVECTOR2(3750, 200), D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 1), 20, 60);
    setEnemy_B(D3DXVECTOR2(3950, 200), D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 1), 20, 60);
    setEnemy_B(D3DXVECTOR2(4150, 200), D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 1), 20, 60);
    setAccelerationBlock(D3DXVECTOR2(4300, 260), D3DXVECTOR2(150, 150), true, DOWN);

    //----------------------------

    setWall(D3DXVECTOR2(4470, 60), D3DXVECTOR2(308, 374), 0);
    setWall(D3DXVECTOR2(4470, 426), D3DXVECTOR2(908, 122), 0);

    setEnemy_B(D3DXVECTOR2(4900, 300), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 80, 120);
    setEnemy_B(D3DXVECTOR2(4900, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 80, 120);

    setWall(D3DXVECTOR2(5600, 60), D3DXVECTOR2(100, 244), 0);
    setWall(D3DXVECTOR2(5600, 426), D3DXVECTOR2(100, 244), 0);

    setAccelerationBlock(D3DXVECTOR2(5478, 60), D3DXVECTOR2(122, 122), true, LEFT);
    setAccelerationBlock(D3DXVECTOR2(5478, 548), D3DXVECTOR2(122, 122), true, UP);

    setEnemy_B(D3DXVECTOR2(5900, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 80, 120);
    setEnemy_B(D3DXVECTOR2(6380, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(-4, 0), 80, 120);
    setEnemy_B(D3DXVECTOR2(6380, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);
    setEnemy_B(D3DXVECTOR2(5900, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4), 80, 120);

    setGoal(D3DXVECTOR2(6480, 580), D3DXVECTOR2(150, 128), 1);



}