

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
#include "timer.h"


void SetSCENE_3_4() {

    AddTimer(100);

    ////プレイヤー召喚
    setPlayer(D3DXVECTOR2(150, 600), D3DXVECTOR2(0, 0));
    ////ボール
    setBall(D3DXVECTOR2(200, 550), D3DXVECTOR2(0, 0));

    //基本ブロック
    setWall(D3DXVECTOR2(0, 669), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(60, 720), 0);
    setWall(D3DXVECTOR2(7227, 0), D3DXVECTOR2(60, 720), 0);

    setEnemy_B(D3DXVECTOR2(410, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(890, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(-4, 0),60, 120);
    setEnemy_B(D3DXVECTOR2(890, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);
    setEnemy_B(D3DXVECTOR2(410, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4),60, 120);

    setWall(D3DXVECTOR2(1000, 510), D3DXVECTOR2(300, 160), 0);
    setWall_B(D3DXVECTOR2(1000, 50), D3DXVECTOR2(150, 160), 20);
    setWall_B(D3DXVECTOR2(1000, 210), D3DXVECTOR2(150, 150), 20);
    setWall_B(D3DXVECTOR2(1000, 360), D3DXVECTOR2(150, 150), 20);

    setWall(D3DXVECTOR2(1150, 360), D3DXVECTOR2(300, 180), 0);
    setWall_B(D3DXVECTOR2(1150, 50), D3DXVECTOR2(150, 160), 20);
    setWall_B(D3DXVECTOR2(1150, 210), D3DXVECTOR2(150, 150), 20);

    setWall(D3DXVECTOR2(1300, 210), D3DXVECTOR2(300, 150), 0);
    setWall_B(D3DXVECTOR2(1300, 50), D3DXVECTOR2(150, 160), 20);


    setEnemy_B(D3DXVECTOR2(1400, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(1, 0), 60, 10);

    setWall_B(D3DXVECTOR2(1450, 360), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(1600, 360), D3DXVECTOR2(150, 150), 0);

    setEnemy_B(D3DXVECTOR2(1850, 275), D3DXVECTOR2(128, 128), D3DXVECTOR2(1, 0), 80, 10);

    setWall(D3DXVECTOR2(1750, 360), D3DXVECTOR2(400, 180), 0);
    for (int i = 0; i < 13; i++)
    {
        setWall_B(D3DXVECTOR2(1750 +(130 * i), 540), D3DXVECTOR2(130, 130), 0);
    }
    setWall(D3DXVECTOR2(1900, 210), D3DXVECTOR2(250, 150), 0);
    setWall(D3DXVECTOR2(2050, 60), D3DXVECTOR2(100, 150), 0);

    setSlowfield(D3DXVECTOR2(2150, 420), D3DXVECTOR2(100, 120), 0.1f);
    setWall(D3DXVECTOR2(2250, 420), D3DXVECTOR2(1200, 120), 0);

    setWall(D3DXVECTOR2(2400, 180), D3DXVECTOR2(1200, 120), 0);
    for (int i = 0; i < 10; i++)
    {
        setWall_B(D3DXVECTOR2(2400 + (120 * i), 300), D3DXVECTOR2(120, 120), 40);
    }

    setSlowfield(D3DXVECTOR2(2490, 60), D3DXVECTOR2(120, 120), 0.1f);

    setEnemy_B(D3DXVECTOR2(2700, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 80, 180);
    setEnemy_B(D3DXVECTOR2(3525, 350), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 3), 80, 120);
    setEnemy_B(D3DXVECTOR2(3900, 115), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);


    setWall(D3DXVECTOR2(3600, 180), D3DXVECTOR2(200, 490), 0);

    setWall(D3DXVECTOR2(4000, 60), D3DXVECTOR2(600, 460), 0);

    for (int i = 0; i < 4; i++)
    {
        setWall_B(D3DXVECTOR2(4000 + (150 * i), 520), D3DXVECTOR2(150, 150), 40);
    }

    //--------------------
    setEnemy_B(D3DXVECTOR2(4700, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(1, 4), 80, 120);
    setEnemy_B(D3DXVECTOR2(4900, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(-1, 4), 80, 120);

    setWall_B(D3DXVECTOR2(5000, 365), D3DXVECTOR2(150, 155), 40);
    setWall_B(D3DXVECTOR2(5000, 210), D3DXVECTOR2(150, 155), 40);

    setSlowboundwall(D3DXVECTOR2(5000, 60), D3DXVECTOR2(150, 150), 0.1f);
    setSlowboundwall(D3DXVECTOR2(5000, 520), D3DXVECTOR2(150, 150), 0.1f);

    setEnemy_B(D3DXVECTOR2(5250, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);
    setEnemy_B(D3DXVECTOR2(5670, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);

    setWall(D3DXVECTOR2(5400, 60), D3DXVECTOR2(150, 150), 0);
    setWall(D3DXVECTOR2(5400, 370), D3DXVECTOR2(150, 150), 0);
    setAccelerationBlock(D3DXVECTOR2(5400, 520), D3DXVECTOR2(150, 150), true, LEFT);

    setSlowfield(D3DXVECTOR2(5400, 210), D3DXVECTOR2(150, 160), 0.05f);

    setWall(D3DXVECTOR2(5800, 60), D3DXVECTOR2(500, 244), 0);
    setSlowfield(D3DXVECTOR2(5800, 2440), D3DXVECTOR2(120, 120), 0.05f);

    for (int i = 0; i < 4; i++)
    {
        setWall_B(D3DXVECTOR2(5800 + (125 * i), 302), D3DXVECTOR2(125, 122), 20 * i);
    }
    setWall(D3DXVECTOR2(5800, 422), D3DXVECTOR2(500, 250), 0);

    setEnemy_B(D3DXVECTOR2(6350, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 80, 120);

    setGoal(D3DXVECTOR2(6480, 580), D3DXVECTOR2(150, 128), 1);



}