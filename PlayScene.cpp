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
	}
	pPlayer_[0]->SetObjectName("PlayerFirst");
	pPlayer_[1]->SetObjectName("PlayerSeconds");
	pSky_ = Instantiate<Sky>(this);
	pSky_->SetObjectName("SkyFirst");
	pCamera_ = new Camera;
	XMFLOAT3 PlayerPos = { 3,0,0 };
	XMFLOAT3 skyRot = { 0,150,90 };
	XMFLOAT3 skyPos = { 0, -100, 0 };
	pSky_->SetRotate(skyRot);
	pSky_->SetPosition(skyPos);
	camPos_.x = 0;
	camPos_.y = 5;
	camPos_.z = -10;
	pPlayer_[0]->SetPosition(PlayerPos);

}

void PlayScene::Update()
{
	for (int j = 0u; j <= 1; j++)
	{
		XMFLOAT3 mouse;
		XMVECTOR rot;
		//Input::SetMousePosition(800,600);
		mouse = Input::GetMouseMove();
		const float sensitivity = 50;
		camPos_.x += mouse.x / sensitivity;
		camPos_.y += mouse.y / sensitivity;
		camPos_.z += mouse.z;
		//camPos_ = pPlayer_[j]->GetPosition();
		//camPos_.y += 5;
		//camPos_.z += -10;
		pCamera_->SetPosition(camPos_, j);
		pCamera_->SetTarget(pPlayer_[j]->GetPosition(), j);
	}

}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
