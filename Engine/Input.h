#pragma once
//インクルード
#include <dInput.h>
#include "Direct3D.h"
//リンカ
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

/// <summary>
/// DirectInputを使ったキーボード入力処理
/// </summary>
namespace Input
{
	void Initialize(HWND _hWnd);
	void Update();
	void Release();
	//▼キーボード
	bool IsKey(int _keyCode);
	bool IsKeyDown(int _keyCode);
	bool IsKeyUp(int _keyCode);
	//▼マウス
	bool IsMouseButton(int _buttonCode);
	bool IsMouseButtonDown(int _buttonCode);
	bool IsMouseButtonUp(int _buttonCode);
	//▼ゲッター・セッター
	XMFLOAT3 GetMousePosition();
	XMFLOAT3 GetMouseMove();
	void SetMousePosition(int _x, int _y);
};
