//インクルード
#include <Windows.h>
#include <stdlib.h>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Rootjob.h"
#include "Engine/Model.h"

#pragma comment(lib, "winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名

Rootjob* pRootjob = nullptr;
Camera* pCamera = new Camera;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HRESULT hr;

	//初期化ファイル(setup.ini)から必要な情報を取得
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");
	int fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		caption,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,               //ウィンドウ幅
		winH,               //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Direct3Dの初期化に失敗", "エラー", MB_OK);
		PostQuitMessage(0); //エラー起きたら強制終了
		return hr;
	}

	//カメラの初期化
	pCamera->Initialize();

	//DirectInputの初期化
	Input::Initialize(hWnd);

	pRootjob = new Rootjob(nullptr);
	pRootjob->Initialize();

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//メッセージなし
		else
		{
			timeBeginPeriod(1);

			static DWORD countFps = 0;

			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if (nowTime - startTime >= 1000)
			{
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime) * 60 <= 1000)
			{
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;


			timeEndPeriod(1);

			if (Input::IsKeyUp(DIK_ESCAPE))
			{
				PostQuitMessage(0);
			}

			//▼ゲームの処理
			for (int i = 0; i < 1; i++)
			{
				Direct3D::BeginDraw(i);

				//カメラの処理
				//Camera::Update();

				//入力の処理
				Input::Update();

				pRootjob->UpdateSub();

				////▼描画
				//Direct3D::BeginDraw(0);
				//Direct3D::BeginDraw(1);

				//ルートジョブから、すべてのオブジェクトのドローを呼ぶ
				pRootjob->DrawSub();

				Direct3D::EndDraw();

			}
		}
	}

	Model::Release();
	pRootjob->ReleaseSub();
	SAFE_DELETE(pRootjob);

	Input::Release();
	Direct3D::Release();

	return S_OK;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}