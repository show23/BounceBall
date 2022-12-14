

//ヘッダー定義
#include "TEST_SCENE.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "Background.h"
#include "Scroll.h"
#include "Wind.h"

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



void SetSCENE_2_2() {

    ////プレイヤー召喚
    setPlayer(D3DXVECTOR2(150, 450), D3DXVECTOR2(0, 0));
    ////ボール
    setBall(D3DXVECTOR2(200, 450), D3DXVECTOR2(0, 0));

    //基本ブロック
    setWall(D3DXVECTOR2(0, 669), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(60, 720), 0);
    setWall(D3DXVECTOR2(7227, 0), D3DXVECTOR2(60, 720), 0);

    setWall(D3DXVECTOR2(1000, 60), D3DXVECTOR2(150, 280), 0);
    setWall(D3DXVECTOR2(1000, 340), D3DXVECTOR2(700, 100), 0);


    setWarpBox(D3DXVECTOR2(1300, 510), D3DXVECTOR2(150, 150), D3DXVECTOR2(1200, 200), D3DXVECTOR2(70, 50), true, true);

    setWall(D3DXVECTOR2(1500, 340), D3DXVECTOR2(200, 420), 0);

    setWall_B(D3DXVECTOR2(1350, 60), D3DXVECTOR2(140, 140), 0);
    setWall_B(D3DXVECTOR2(1350, 200), D3DXVECTOR2(140, 140), 0);

    setEnemy_B(D3DXVECTOR2(1850, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 90, 60);

    setWall(D3DXVECTOR2(2000, 60), D3DXVECTOR2(100, 400), 0);

    setEnemy_B(D3DXVECTOR2(2175, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 90, 60);

    setWall(D3DXVECTOR2(2400, 180), D3DXVECTOR2(600, 100), 0);
    setWall(D3DXVECTOR2(2250, 420), D3DXVECTOR2(750, 100), 0);

    setWall_B(D3DXVECTOR2(2480, 60), D3DXVECTOR2(120, 120), 0);
    setWall_B(D3DXVECTOR2(2600, 60), D3DXVECTOR2(120, 120), 0);
    setWall_B(D3DXVECTOR2(2720, 60), D3DXVECTOR2(120, 120), 0);

    setWall_B(D3DXVECTOR2(2500, 280), D3DXVECTOR2(140, 140), 0);
    setWall_B(D3DXVECTOR2(2640, 280), D3DXVECTOR2(140, 140), 0);
    setWall_B(D3DXVECTOR2(2780, 280), D3DXVECTOR2(140, 140), 0);

    setWall_B(D3DXVECTOR2(2380, 520), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(2530, 520), D3DXVECTOR2(150, 150), 0);
    setWall_B(D3DXVECTOR2(2680, 520), D3DXVECTOR2(150, 150), 0);

    setWall(D3DXVECTOR2(3000, 60), D3DXVECTOR2(300, 220), 0);
    setWall(D3DXVECTOR2(3000, 420), D3DXVECTOR2(100, 250), 0);

    setWarpBox(D3DXVECTOR2(2850, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(2850, 100), D3DXVECTOR2(70, 50), true, true);

    setEnemy_B(D3DXVECTOR2(3200, 350), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 3), 90, 60);
    setEnemy_B(D3DXVECTOR2(3200, 550), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 90, 60);
    setEnemy_B(D3DXVECTOR2(3600, 550), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 90, 60);

    setWall(D3DXVECTOR2(3300, 60), D3DXVECTOR2(100, 450), 0);
    setWall(D3DXVECTOR2(3400, 210), D3DXVECTOR2(600, 200), 0);
    setWall(D3DXVECTOR2(3400, 410), D3DXVECTOR2(600, 100), 0);
    setWall(D3DXVECTOR2(4200, 410), D3DXVECTOR2(200, 100), 0);

    setEnemy_B(D3DXVECTOR2(4100, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 90, 60);

    setWarpBox(D3DXVECTOR2(4300, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(3450, 100), D3DXVECTOR2(70, 50), true, true);

    setWall_B(D3DXVECTOR2(3600, 60), D3DXVECTOR2(120, 150), 0);
    setWall_B(D3DXVECTOR2(3720, 60), D3DXVECTOR2(120, 150), 0);
    setWall_B(D3DXVECTOR2(3840, 60), D3DXVECTOR2(120, 150), 0);

    setEnemy_B(D3DXVECTOR2(4400, 150), D3DXVECTOR2(128, 128), D3DXVECTOR2(3, 0), 90, 60);
    setEnemy_B(D3DXVECTOR2(4400, 350), D3DXVECTOR2(128, 128), D3DXVECTOR2(3, 0), 90, 60);

    setWall(D3DXVECTOR2(4400, 410), D3DXVECTOR2(300, 260), 0);

    setWall(D3DXVECTOR2(4700, 410), D3DXVECTOR2(200, 260), 0);

    setWarpBox(D3DXVECTOR2(4930, 560), D3DXVECTOR2(100, 100), D3DXVECTOR2(5230, 100), D3DXVECTOR2(70, 50), true, true);

    setWall(D3DXVECTOR2(5050, 60), D3DXVECTOR2(150, 650), 0);

    setWarpBox(D3DXVECTOR2(5200, 560), D3DXVECTOR2(150, 100), D3DXVECTOR2(5600, 100), D3DXVECTOR2(70, 50), true, true);
    setWall_B(D3DXVECTOR2(5200, 200), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5200, 300), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5200, 400), D3DXVECTOR2(150, 100), 0);

    setWall(D3DXVECTOR2(5350, 60), D3DXVECTOR2(200, 650), 0);

    setWarpBox(D3DXVECTOR2(5540, 560), D3DXVECTOR2(150, 100), D3DXVECTOR2(5940, 100), D3DXVECTOR2(70, 50), true, true);
    setWall_B(D3DXVECTOR2(5550, 200), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5550, 300), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5550, 400), D3DXVECTOR2(150, 100), 0);

    setWall(D3DXVECTOR2(5700, 60), D3DXVECTOR2(200, 650), 0);

    setWarpBox(D3DXVECTOR2(5900, 560), D3DXVECTOR2(150, 100), D3DXVECTOR2(6300, 100), D3DXVECTOR2(70, 50), true, true);
    setWall_B(D3DXVECTOR2(5900, 200), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5900, 300), D3DXVECTOR2(150, 100), 0);
    setWall_B(D3DXVECTOR2(5900, 400), D3DXVECTOR2(150, 100), 0);

    setWall(D3DXVECTOR2(6050, 60), D3DXVECTOR2(200, 650), 0);


    setEnemy_B(D3DXVECTOR2(6345, 450), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 20, 60);


    setGoal(D3DXVECTOR2(6800, 580), D3DXVECTOR2(150, 128), 1);


}