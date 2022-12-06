/*==============================================================================

   テクスチャの描画 [main.cpp]
                                                         Author : Joy
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include <time.h>
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "scene.h"

#include "sprite.h"
#include "fade.h"


#include "game.h"
#include "Scroll.h"
#include "Player.h"
#include "Ball.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"BounceBall"			// ウインドウのクラス名
#define WINDOW_CAPTION		"BounceBall teamOctopus "			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

bool gamestate = 1;
#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

FILE* out = 0;
HANDLE Console;
COORD CursorPos;

POINT mouse;
#endif
											
											
//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	
	

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	//アイコン画像の設定
	//	wcex.hIcon = LoadIconA(hInstance, (LPCTSTR)"APP_ICON");
	//挫折

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);


	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_VISIBLE,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);
	

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	


	// メッセージループ
	while(gamestate)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけ情報を表示する

				wsprintf(g_DebugStr, WINDOW_CAPTION);

				GetCursorPos(&mouse);
				ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &mouse);
				
				mouse.x += (int)getWorldPos().x - (int)(SCREEN_WIDTH/2);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "   X: %ld", mouse.x);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "   Y: %ld", mouse.y);

				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				CheckScene();

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
#ifdef _DEBUG
	AllocConsole();
	(void)freopen_s(&out, "CON", "w", stdout);
	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	CursorPos.X = 0;
	CursorPos.Y = 0;
#endif // _DEBUG


	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// サウンド処理の初期化
	InitSound(hWnd);

	InitFade();

	// スプライトの初期化
	InitSprite();

	SetFadeColor(1.0f, 1.0f, 1.0f);

	SceneFadeIn(SCENE_LOGO);

	//ゲームの初期化
	//InitGame();

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	fclose(out);
	FreeConsole();
#endif // _DEBUG



	// スプライトの終了処理
	UninitSprite();

	// 頂点管理の終了処理
	UninitFade();
	
	// ゲームの終了処理
	//UninitGame();

	// テクスチャの解放
	UninitTexture();

	// サウンドの終了処理
	StopSoundAll();
	UninitSound();

	// 入力の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
#ifdef _DEBUG
	SetConsoleCursorPosition(Console, CursorPos);
#endif // _DEBUG

	//入力系の更新処理
	UpdateInput();



	UpdateScene();

	// ゲームの更新処理
	//UpdateGame();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// シーンの描画処理
	DrawScene();

	// ゲームの描画処理
	//DrawGame();





	// バックバッファ、フロントバッファ入れ替え
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}


void GAMEEND() {
	gamestate = 0;
}