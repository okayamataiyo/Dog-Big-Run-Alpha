#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Item.h"
#include "Controller.h"

PlayScene::PlayScene()
	:GameObject(nullptr, "")
{
}

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
	XMFLOAT3 PlayerPos = { 3,0,0 };
	pPlayer_[0]->SetPosition(PlayerPos);
	pSky_ = Instantiate<Sky>(this);
	pSky_->SetObjectName("SkyFirst");
	Instantiate<Controller>(this);
	XMFLOAT3 skyRot = { 0,150,90 };
	XMFLOAT3 skyPos = { 0, -100, 0 };
	pSky_->SetRotate(skyRot);
	pSky_->SetPosition(skyPos);

}

void PlayScene::Update()
{


}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
