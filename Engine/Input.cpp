#include "Input.h"
#include "Direct3D.h"

namespace Input
{
	HWND hWnd_;								//�E�B���h�E�n���h��
	LPDIRECTINPUT8 pDInput_;				//DirectInput�I�u�W�F�N�g
	//���L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice_;		//�L�[�{�[�h�I�u�W�F�N�g
	BYTE KeyState_[256];					//���݂̊e�L�[�̏��
	BYTE prevKeyState_[256];				//�O�t���[���ł̊e�L�[�̏��
	//���}�E�X
	LPDIRECTINPUTDEVICE8 pMouseDevice_;		//�}�E�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePosition_;				//�}�E�X�J�[�\���̈ʒu

	void Initialize(HWND _hWnd)
	{
		hWnd_ = _hWnd;

		//��DirectInput�{��
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, 
			(VOID**)&pDInput_, nullptr);

		//���L�[�{�[�h
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(NULL,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//���}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		//���L�[�{�[�h
		pKeyDevice_->Acquire();
		memcpy(prevKeyState_, KeyState_, sizeof(prevKeyState_));
		pKeyDevice_->GetDeviceState(sizeof(KeyState_), &KeyState_);
		//���}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	}

	void Release()
	{
		SAFE_RELEASE(pDInput_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}

	//���L�[�{�[�h
	bool IsKey(int _keyCode)
	{
		if (KeyState_[_keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int _keyCode)
	{
		if (IsKey(_keyCode) && !(prevKeyState_[_keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int _keyCode)
	{
		if (!IsKey(_keyCode) && (prevKeyState_[_keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//���}�E�X
	bool IsMouseButton(int _buttonCode)
	{
		if (mouseState_.rgbButtons[_buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int _buttonCode)
	{
		if (IsMouseButton(_buttonCode) && !(prevMouseState_.rgbButtons[_buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int _buttonCode)
	{
		if (!IsMouseButton(_buttonCode) && prevMouseState_.rgbButtons[_buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	XMFLOAT3 GetMousePosition()
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePosition_.x, (float)mousePosition_.y, 0);
		return result;
	}

	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}

	void SetMousePosition(int _x, int _y)
	{
		mousePosition_.x = _x;
		mousePosition_.y = _y;
	}
}