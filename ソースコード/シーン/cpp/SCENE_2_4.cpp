

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



void SetSCENE_2_4() {
    ////プレイヤー召喚
    setPlayer(D3DXVECTOR2(150, 600), D3DXVECTOR2(0, 0));
    ////ボール
    setBall(D3DXVECTOR2(200, 550), D3DXVECTOR2(0, 0));

    //基本ブロック
    setWall(D3DXVECTOR2(0, 669), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(60, 720), 0);
    setWall(D3DXVECTOR2(7227, 0), D3DXVECTOR2(60, 720), 0);

    setWall(D3DXVECTOR2(60, 60), D3DXVECTOR2(700, 360), 0);
    setWall(D3DXVECTOR2(760, 60), D3DXVECTOR2(300, 610), 0);

    setWarpBox(D3DXVECTOR2(600, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(1100, 100), D3DXVECTOR2(70, 50), true, true);

    setAccelerationBlock(D3DXVECTOR2(1500, 60), D3DXVECTOR2(150, 150), true, RIGHT);

    setWall(D3DXVECTOR2(1060, 210), D3DXVECTOR2(600, 460), 0);

    //-----------------------------------
    setEnemy_B(D3DXVECTOR2(1750, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(5, 0), 60, 120);

    setWall_B(D3DXVECTOR2(1660, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1660, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1660, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(1770, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1770, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1770, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(1880, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1880, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1880, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(1990, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1990, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(1990, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(2100, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2100, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2100, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(2210, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2210, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2210, 560), D3DXVECTOR2(110, 110), 0);

    setWall_B(D3DXVECTOR2(2320, 340), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2320, 450), D3DXVECTOR2(110, 110), 0);
    setWall_B(D3DXVECTOR2(2320, 560), D3DXVECTOR2(110, 110), 0);

    setWarpBox(D3DXVECTOR2(2500, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(2700, 100), D3DXVECTOR2(70, 50), true, true);

    setWall(D3DXVECTOR2(2600, 210), D3DXVECTOR2(600, 460), 0);

    setAccelerationBlock(D3DXVECTOR2(3000, 60), D3DXVECTOR2(150, 150), true, RIGHT);
    //-----------------------------------
    setEnemy_B(D3DXVECTOR2(3300, 400), D3DXVECTOR2(128, 128), D3DXVECTOR2(2, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(3750, 200), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 3), 20, 120);
    setEnemy_B(D3DXVECTOR2(4000, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(2, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(4000, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(2, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(4400, 380), D3DXVECTOR2(128, 128), D3DXVECTOR2(-2, 0), 60, 120);

    setWall(D3DXVECTOR2(3600, 60), D3DXVECTOR2(100, 610), 0);
    setWall(D3DXVECTOR2(3800, 60), D3DXVECTOR2(100, 610), 0);

    setWall(D3DXVECTOR2(3200, 210), D3DXVECTOR2(300, 100), 0);
    setWall(D3DXVECTOR2(3300, 460), D3DXVECTOR2(300, 100), 0);
    setWall(D3DXVECTOR2(4000, 210), D3DXVECTOR2(400, 100), 0);
    setWall(D3DXVECTOR2(3900, 460), D3DXVECTOR2(400, 100), 0);

    setWarpBox(D3DXVECTOR2(3200, 570), D3DXVECTOR2(100, 100), D3DXVECTOR2(3900, 60), D3DXVECTOR2(100, 100), true, true);
    setWarpBox(D3DXVECTOR2(3500, 570), D3DXVECTOR2(100, 100), D3DXVECTOR2(4400, 60), D3DXVECTOR2(100, 100), true, true);
    setWarpBox(D3DXVECTOR2(3900, 570), D3DXVECTOR2(100, 100), D3DXVECTOR2(3700, 60), D3DXVECTOR2(100, 100), true, true);
    setWarpBox(D3DXVECTOR2(3700, 570), D3DXVECTOR2(100, 100), D3DXVECTOR2(4650, 580), D3DXVECTOR2(70, 50), true, true);

    //-----------------------------------

    setWall(D3DXVECTOR2(4500, 60), D3DXVECTOR2(100, 610), 0);

    setWarpBox(D3DXVECTOR2(5350, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(4650, 100), D3DXVECTOR2(70, 50), true, true);
    setWarpBox(D3DXVECTOR2(5350, 80), D3DXVECTOR2(100, 100), D3DXVECTOR2(4650, 360), D3DXVECTOR2(70, 50), true, true);

    setWall(D3DXVECTOR2(4600, 210), D3DXVECTOR2(900, 100), 0);

    setWall_B(D3DXVECTOR2(4800, 60), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(4950, 60), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(5100, 60), D3DXVECTOR2(150, 150), 0);

    setWall(D3DXVECTOR2(4600, 460), D3DXVECTOR2(350, 100), 0);
    setWall(D3DXVECTOR2(5150, 460), D3DXVECTOR2(350, 100), 0);

    setWall_B(D3DXVECTOR2(4800, 310), D3DXVECTOR2(150, 150), 0);

    setWall_B(D3DXVECTOR2(5150, 310), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(5300, 310), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(5450, 310), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(5600, 310), D3DXVECTOR2(150, 150), 0);

    setWall(D3DXVECTOR2(5500, 60), D3DXVECTOR2(300, 250), 0);
    setWall(D3DXVECTOR2(5500, 460), D3DXVECTOR2(300, 250), 0);

    setEnemy_B(D3DXVECTOR2(5900, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(6380, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(-4, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(6380, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);
    setEnemy_B(D3DXVECTOR2(5900, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4), 60, 120);

    setGoal(D3DXVECTOR2(6480, 580), D3DXVECTOR2(150, 128), 1);



}