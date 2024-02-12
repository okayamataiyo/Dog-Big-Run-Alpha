#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Controller::Controller(GameObject* _pParent)
{
}

Controller::~Controller()
{
}

void Controller::Initialize()
{
	for (int i = 0u; i <= 1; i++)
	{
		camPos_[i].x = 0;
		camPos_[i].y = 5;
		camPos_[i].z = -10;
	}
	pCamera_ = new Camera;
	pPlayScene_ = new PlayScene;
}

void Controller::Update()
{
	for (int j = 0u; j <= 1; j++)
	{
		XMMATRIX mRotY[2];
		mRotY[j] = XMMatrixRotationY(XMConvertToRadians(pPlayScene_->GetPlayer(j).GetRotate().y));
		XMMATRIX mRotX[2];
		mRotX[j] = XMMatrixRotationX(XMConvertToRadians(pPlayScene_->GetPlayer(j).GetRotate().x));

		XMVECTOR vPos[2];
		vPos[j] = pPlayScene_->GetPlayer(j).GetVecPos();

		XMVECTOR frontMove[2];
		frontMove[j] = XMVectorSet(0, 0, 0.1f, 0);
		frontMove[j] = XMVector3TransformCoord(frontMove[j], mRotY[j]);
		XMVECTOR rightMove[2];
		rightMove[j] = XMVectorSet(0.1f, 0, 0, 0);
		rightMove[j] = XMVector3TransformCoord(rightMove[j], mRotY[j]);
		XMVECTOR vMove1[2];
		vMove1[j] = { 0.0f, 0.0f, 0.1f, 0.0f };
		vMove1[j] = XMVector3TransformCoord(vMove1[j], mRotY[j]);
		XMVECTOR vMove2[2];
		vMove2[j] = { 0.1f, 0.0f, 0.0f, 0.0f };          //‰¡‚É0.1m
		vMove2[j] = XMVector3TransformCoord(vMove2[j], mRotY[j]);
		XMVECTOR vMove3[2];
		vMove3[j] = { 0.0f, 0.1f, 0.0f, 0.0f };          //c‚É0.1m
		vMove3[j] = XMVector3TransformCoord(vMove3[j], mRotY[j]);
		XMFLOAT3 mouse;
		XMVECTOR rot;

		//Input::SetMousePosition(800,600);
		mouse = Input::GetMouseMove();
		const float sensitivity = 50;
		if (camPos_[j].y >= 88)
		{
			camPos_[j].y = 87;
		}
		if (camPos_[j].y <= 0)
		{
			camPos_[j].y = 1;
		}
		camPos_[j].y += mouse.y / sensitivity;
		camPos_[j].x -= mouse.x / sensitivity;
		camPos_[j].z += mouse.z / 1000;
		XMVECTOR veccamPos_[2];
		veccamPos_[j] = XMLoadFloat3(&camPos_[j]);
		veccamPos_[j] = XMVector3TransformCoord(veccamPos_[j], mRotX[j] * mRotY[j]);
		//camPos_ = pPlayer_[j]->GetPosition();
		//camPos_.y += 5;
		//camPos_.z += -10;
		pCamera_->SetPosition(vPos[j] + veccamPos_[j], j);
		pCamera_->SetTarget(pPlayScene_->GetPlayer(j).GetPosition(), j);
	}
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
