#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Sky.h"

PlayScene::PlayScene(GameObject* _parent)
	:GameObject(_parent, "PlayScene")
{
	
}

void PlayScene::Initialize()
{
	Instantiate<Item>(this);
	for (int i = 0u; i <= 1; i++)
	{
		pPlayer_[i] = Instantiate<Player>(this);
	}
	pPlayer_[0]->SetObjectName("PlayerFirst");
	pPlayer_[1]->SetObjectName("PlayerSecond");
	Instantiate<Stage>(this);
	Instantiate<Sky>(this);
	pCamera_ = new Camera;
	XMFLOAT3 position = { 3,0,0 };
	pPlayer_[0]->SetTransform(position);

}

void PlayScene::Update()
{
	for (int j = 0u; j <= 1; j++)
	{
		camPos_ = pPlayer_[j]->GetPlayerPos().position_;
		camPos_.y += 2;
		camPos_.z -= 15;
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
