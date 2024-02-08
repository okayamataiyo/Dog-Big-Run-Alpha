#pragma once
//�C���N���[�h
#include <dInput.h>
#include "Direct3D.h"
//�����J
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

/// <summary>
/// DirectInput���g�����L�[�{�[�h���͏���
/// </summary>
namespace Input
{
	void Initialize(HWND _hWnd);
	void Update();
	void Release();
	//���L�[�{�[�h
	bool IsKey(int _keyCode);
	bool IsKeyDown(int _keyCode);
	bool IsKeyUp(int _keyCode);
	//���}�E�X
	bool IsMouseButton(int _buttonCode);
	bool IsMouseButtonDown(int _buttonCode);
	bool IsMouseButtonUp(int _buttonCode);
	//���Q�b�^�[�E�Z�b�^�[
	XMFLOAT3 GetMousePosition();
	XMFLOAT3 GetMouseMove();
	void SetMousePosition(int _x, int _y);
};
