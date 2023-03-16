

//�w�b�_�[��`
#include "TEST_SCENE.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "Background.h"
#include "Scroll.h"

#include "Player.h"
#include "Ball.h"

/*--------------------------------------
    �ǉ��w�b�_�[��`(�Y��Ȃ��ł�)
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



void SetSCENE_3_3() {
    ////�v���C���[����
    setPlayer(D3DXVECTOR2(150, 60), D3DXVECTOR2(0, 0));
    ////�{�[��
    setBall(D3DXVECTOR2(200, 100), D3DXVECTOR2(0, 0));

    //��{�u���b�N
    setWall(D3DXVECTOR2(0, 669), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(7287, 60), 0);
    setWall(D3DXVECTOR2(0, 0), D3DXVECTOR2(60, 720), 0);
    setWall(D3DXVECTOR2(7227, 0), D3DXVECTOR2(60, 720), 0);

    setWall(D3DXVECTOR2(60, 210), D3DXVECTOR2(1000, 460), 0);

    setEnemy_B(D3DXVECTOR2(1115, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);

    setBumper(D3DXVECTOR2(1400, 200), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(1800, 400), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(1200, 300), D3DXVECTOR2(75, 75), 5);

    setWall(D3DXVECTOR2(2100, 60), D3DXVECTOR2(200, 440), 0);

    setEnemy_B(D3DXVECTOR2(1315, 590), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4), 60, 120);
    setEnemy_B(D3DXVECTOR2(1550, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);
    setEnemy_B(D3DXVECTOR2(1700, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);
    setEnemy_B(D3DXVECTOR2(2000, 590), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4), 60, 120);


    setWall(D3DXVECTOR2(2300, 60), D3DXVECTOR2(1500, 350), 0);

    setSlowfield(D3DXVECTOR2(2300, 410), D3DXVECTOR2(150, 260), 0.05f);

    setEnemy_B(D3DXVECTOR2(2600, 450), D3DXVECTOR2(128, 128), D3DXVECTOR2(2, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(3150, 450), D3DXVECTOR2(128, 128), D3DXVECTOR2(2, 0), 60, 120);

    setSlowboundwall(D3DXVECTOR2(3000, 410), D3DXVECTOR2(80, 80), 0.1f);
    setSlowboundwall(D3DXVECTOR2(3300, 590), D3DXVECTOR2(80, 80), 0.1f);

    setEnemy_B(D3DXVECTOR2(3500, 560), D3DXVECTOR2(128, 128), D3DXVECTOR2(3, 0), 60, 120);

    setBumper(D3DXVECTOR2(2800, 590), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(3200, 590), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(3500, 410), D3DXVECTOR2(75, 75), 5);

    setSlowboundwall(D3DXVECTOR2(3800, 60), D3DXVECTOR2(200, 200), 0.1f);

    setEnemy_B(D3DXVECTOR2(4100, 110), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);

    setWall(D3DXVECTOR2(4200, 60), D3DXVECTOR2(150, 300), 0);
    setBumper(D3DXVECTOR2(4350, 590), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(4400, 60), D3DXVECTOR2(75, 75), 5);
    setWall(D3DXVECTOR2(4200, 590), D3DXVECTOR2(150, 160), 0);

    setEnemy_B(D3DXVECTOR2(4400, 200), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 3), 60, 120);

    setWall(D3DXVECTOR2(4500, 60), D3DXVECTOR2(150, 150), 0);
    setBumper(D3DXVECTOR2(4700, 60), D3DXVECTOR2(75, 75), 5);
    setWall(D3DXVECTOR2(4500, 510), D3DXVECTOR2(150, 160), 0);
    
    setEnemy_B(D3DXVECTOR2(4700, 180), D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 3), 60, 120);

    setSlowfield(D3DXVECTOR2(4500, 210), D3DXVECTOR2(150, 300), 0.05f);

    setBumper(D3DXVECTOR2(4750, 225), D3DXVECTOR2(75, 75), 5);
    setBumper(D3DXVECTOR2(4750, 420), D3DXVECTOR2(75, 75), 5);
    setWall(D3DXVECTOR2(4800, 60), D3DXVECTOR2(1000, 240), 0);
    setWall(D3DXVECTOR2(4800, 420), D3DXVECTOR2(1000, 250), 0);

    setSlowfield(D3DXVECTOR2(4900, 300), D3DXVECTOR2(120, 120), 0.05f);


    setWall_B(D3DXVECTOR2(5020, 300), D3DXVECTOR2(120, 120), 0);
    setWall_B(D3DXVECTOR2(5140, 300), D3DXVECTOR2(120, 120), 0);
    setWall_B(D3DXVECTOR2(5260, 300), D3DXVECTOR2(120, 120), 0);
    setWall_B(D3DXVECTOR2(5380, 300), D3DXVECTOR2(120, 120), 0);

    setEnemy_B(D3DXVECTOR2(5900, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(4, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(6380, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(-4, 0), 60, 120);
    setEnemy_B(D3DXVECTOR2(6380, 120), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, 4), 60, 120);
    setEnemy_B(D3DXVECTOR2(5900, 600), D3DXVECTOR2(128, 128), D3DXVECTOR2(0, -4), 60, 120);

    setGoal(D3DXVECTOR2(6480, 580), D3DXVECTOR2(150, 128), 1);



}