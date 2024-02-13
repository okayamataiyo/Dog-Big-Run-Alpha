#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Item.h"

PlayScene::PlayScene(GameObject* _pParent)
	:GameObject(_pParent, "PlayScene")
{
	
}

void PlayScene::Initialize()
{
	Instantiate<Item>(this);
	Instantiate<Stage>(this);
	for (int i = 0u; i <= 1; i++)
	{
		pPlayer_[i] = Instantiate<Player>(this);
		camVec_[i].x = 0;
		camVec_[i].y = 5;
		camVec_[i].z = -10;
	}
	pPlayer_[0]->SetObjectName("PlayerFirst");
	pPlayer_[1]->SetObjectName("PlayerSeconds");
	pSky_ = Instantiate<Sky>(this);
	pSky_->SetObjectName("SkyFirst");
	pCamera_ = new Camera;
	XMFLOAT3 FPlayerPos = { 3,0,0 };
	XMFLOAT3 SPlayerPos = { -3,0,0 };
	XMFLOAT3 skyRot = { 0,150,90 };
	XMFLOAT3 skyPos = { 0, -100, 0 };
	pSky_->SetRotate(skyRot);
	pSky_->SetPosition(skyPos);
	pPlayer_[0]->SetPosition(FPlayerPos);
	pPlayer_[1]->SetPosition(SPlayerPos);

}

void PlayScene::Update()
{
	for (int i = 0u; i <= 1; i++)
	{
		XMMATRIX mRotY[2];
		mRotY[i] = XMMatrixRotationY(XMConvertToRadians(pPlayer_[i]->GetRotate().y));
		XMMATRIX mRotX[2];
		mRotX[i] = XMMatrixRotationX(XMConvertToRadians(pPlayer_[i]->GetRotate().x));

		XMVECTOR vPos[2];
		vPos[i] = pPlayer_[i]->GetVecPos();

		XMVECTOR frontMove[2];
		frontMove[i] = XMVectorSet(0, 0, 0.1f, 0);
		frontMove[i] = XMVector3TransformCoord(frontMove[i], mRotY[i]);
		XMVECTOR rightMove[2];
		rightMove[i] = XMVectorSet(0.1f, 0, 0, 0);
		rightMove[i] = XMVector3TransformCoord(rightMove[i], mRotY[i]);
		XMVECTOR vMove1[2];
		vMove1[i] = { 0.0f, 0.0f, 0.1f, 0.0f };
		vMove1[i] = XMVector3TransformCoord(vMove1[i], mRotY[i]);
		XMVECTOR vMove2[2];
		vMove2[i] = { 0.1f, 0.0f, 0.0f, 0.0f };          //‰¡‚É0.1m
		vMove2[i] = XMVector3TransformCoord(vMove2[i], mRotY[i]);
		XMVECTOR vMove3[2];
		vMove3[i] = { 0.0f, 0.1f, 0.0f, 0.0f };          //c‚É0.1m
		vMove3[i] = XMVector3TransformCoord(vMove3[i], mRotY[i]);
		XMFLOAT3 mouse;

		//Input::SetMousePosition(800,600);
		mouse = Input::GetMouseMove();
		const float sensitivity = 400;

		static float RotationX[2] = {};
		static float RotationY[2] = {};
		static float vecLength[2] = {};
		static float prevLen[2] = {};
		static float prevRotX[2] = {};

		RotationY[i] = mouse.y;
		RotationX[i] = mouse.x;
		vecLength[i] -= (mouse.z) / 50;

		XMFLOAT3 rDir = { 0,0,1 };
		XMVECTOR Dir = XMLoadFloat3(&rDir);

		//Dir = Dir * (pPlayer_[i]->GetRotate().x + RotationX[i]) * (pPlayer_[i]->GetRotate().y + RotationY[i]);
		//Dir = Dir + (vecLength * 2);
		camVec_[i].y += RotationX[i] / sensitivity;
		camVec_[i].x += RotationY[i] / sensitivity;
		//camVec_[i].z += vecLength[i]  + 10;

		static float EasingX[2] = {};
		static float EasingY[2] = {};

		float sigmaRotY = camVec_[i].y;// + EasingY[i]; +pPlayer_[i]->GetRotate().y;
		float sigmaRotX = camVec_[i].x;// + EasingX[i]; +pPlayer_[i]->GetRotate().x;
		//vecLength[i] = camVec_[i].z;

		//EasingY[j] = (pPlayer_[j]->GetRotate().y * 0.1) + (EasingY[j] * 0.9);
		//EasingX[j] = (pPlayer_[j]->GetRotate().x * 0.1) + (EasingX[j] * 0.9);

		if (sigmaRotX > 0*(3.14/180))
		{
			sigmaRotX = prevRotX[i];
			RotationX[i] = 0;
		}
		if (sigmaRotX < -88*(3.14/180))
		{
			sigmaRotX = prevRotX[i];
			RotationX[i] = 0;
		}

		prevRotX[i] = sigmaRotX;

		XMMATRIX mxRotX = XMMatrixRotationX(sigmaRotX);
		XMMATRIX mxRotY = XMMatrixRotationY(sigmaRotY);

		XMMATRIX rot = mxRotX * mxRotY;
		XMFLOAT3 playerPos = pPlayer_[i]->GetPosition();
		
		Dir = XMVector3Transform(Dir, rot);
		Dir = XMVector3Normalize(Dir);
		Dir = Dir * (vecLength[i] + 10);
		Dir += XMLoadFloat3(&playerPos);
		//camVec_ = pPlayer_[j]->GetPosition();
		//camVec_.y += 5;
		//camVec_.z += -10;
		//auto a = pPlayer_[j]->GetPosition();

		pCamera_->SetPosition(Dir, i);
		pCamera_->SetTarget(pPlayer_[i]->GetPosition(), i);

		prevLen[i] = vecLength[i];
	}
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
