#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Item.h"

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
	Instantiate<Controller>(this);
	pSky_ = Instantiate<Sky>(this);
	pSky_->SetObjectName("SkyFirst");
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
