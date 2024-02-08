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
	for (int i = 0u; i <= 1; i++)
	{
		pPlayer_[i] = Instantiate<Player>(this);
		pSky_[i] = Instantiate<Sky>(this);
	}
	pPlayer_[0]->SetObjectName("PlayerFirst");
	pPlayer_[1]->SetObjectName("PlayerSeconds");
	pSky_[0]->SetObjectName("SkyFirst");
	pSky_[1]->SetObjectName("SkySeconds");
	Instantiate<Stage>(this);
	pCamera_ = new Camera;
	XMFLOAT3 position = { 3,0,0 };
	XMFLOAT3 skyPos = { 0,90,0 };
	pSky_[0]->SetRotate(skyPos);
	camPos_.x = 0;
	camPos_.y = 5;
	camPos_.z = -10;
	pPlayer_[0]->SetTransform(position);

}

void PlayScene::Update()
{
	for (int j = 0u; j <= 1; j++)
	{
		XMFLOAT3 mouse;
		//Input::SetMousePosition(800,600);
		mouse = Input::GetMouseMove();
		camPos_.x += mouse.x;
		camPos_.y += mouse.y;
		camPos_.z += mouse.z;
		//camPos_.x = pPlayer_[j]->GetPlayerPos().position_.x;
		//camPos_.y = pPlayer_[j]->GetPlayerPos().position_.y;
		//camPos_.z = pPlayer_[j]->GetPlayerPos().position_.z;
		pCamera_->SetPosition(camPos_, j);
		pCamera_->SetTarget(pPlayer_[j]->GetPlayerPos().position_, j);
	}

}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
