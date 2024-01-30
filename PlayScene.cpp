#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"


PlayScene::PlayScene(GameObject* _parent)
	:GameObject(_parent, "PlayScene")
{
	
}

void PlayScene::Initialize()
{
	Instantiate<Item>(this);
	for (int i = 0; i <= 1; i++)
	{
		pPlayer_[i] = Instantiate<Player>(this);
	}
	pPlayer_[0]->SetObjectName("PlayerFirst");
	pPlayer_[1]->SetObjectName("PlayerSecond");
	Instantiate<Stage>(this);

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
