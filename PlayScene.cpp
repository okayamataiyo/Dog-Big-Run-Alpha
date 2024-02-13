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
	for (int j = 0u; j <= 1; j++)
	{
		XMMATRIX mRotY[2];
		mRotY[j] = XMMatrixRotationY(XMConvertToRadians(pPlayer_[j]->GetRotate().y));
		XMMATRIX mRotX[2];
		mRotX[j] = XMMatrixRotationX(XMConvertToRadians(pPlayer_[j]->GetRotate().x));

		XMVECTOR vPos[2];
		vPos[j] = pPlayer_[j]->GetVecPos();

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

		//Input::SetMousePosition(800,600);
		mouse = Input::GetMouseMove();
		const float sensitivity = 50;
		if (camVec_[j].x >= 88)
		{
			camVec_[j].x = 87;
		}
		if (camVec_[j].x <= 0)
		{
			camVec_[j].x = 1;
		}
		static float RotationX[2] = {};
		static float RotationY[2] = {};
		static float vecLength[2] = {};
		static float prevLen[2] = {};

		RotationY[j] = mouse.y;
		RotationX[j] = mouse.x;
		vecLength[j] += (mouse.z -prevLen[j]) / 10;

		XMFLOAT3 rDir = { 0,0,1 };
		XMVECTOR Dir = XMLoadFloat3(&rDir);

		//Dir = Dir * (pPlayer_[j]->GetRotate().x + RotationX[j]) * (pPlayer_[j]->GetRotate().y + RotationY[j]);
		//Dir = Dir + (vecLength * 2);
		camVec_[j].y += RotationX[j] / sensitivity;
		camVec_[j].x += RotationY[j] / sensitivity;
		camVec_[j].z = vecLength[j]  + 10;

		float sigmaRotY = camVec_[j].y + pPlayer_[j]->GetRotate().y;
		float sigmaRotX = camVec_[j].x + pPlayer_[j]->GetRotate().x;
		vecLength[j] = camVec_[j].z;

		XMMATRIX mxRotX = XMMatrixRotationX(sigmaRotX);
		XMMATRIX mxRotY = XMMatrixRotationY(sigmaRotY);

		XMMATRIX rot = mxRotY * mxRotX;
		XMFLOAT3 playerPos = pPlayer_[j]->GetPosition();
		
		Dir = XMVector3Transform(Dir, rot);
		Dir = XMVector3Normalize(Dir);
		Dir = Dir * vecLength[j];
		Dir += XMLoadFloat3(&playerPos);
		//camVec_ = pPlayer_[j]->GetPosition();
		//camVec_.y += 5;
		//camVec_.z += -10;
		//auto a = pPlayer_[j]->GetPosition();

		pCamera_->SetPosition(Dir, j);
		pCamera_->SetTarget(pPlayer_[j]->GetPosition(), j);

		prevLen[j] = (mouse.z -prevLen[j]) / 2;
	}
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
