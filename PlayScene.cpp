#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"


PlayScene::PlayScene(GameObject* _parent)
	:GameObject(_parent, "PlayScene"),pCamera_(nullptr)
{
	
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	for (int i = 0; i <= 1; i++)
	{
		pPlayer_[i] = Instantiate<Player>(this);
	}
	pPlayer_[0]->SetObjectName("PlayerFist");
	pPlayer_[1]->SetObjectName("PlayerSecond");

	pCamera_ = new Camera;
	pCamera_->SetTarget(pPlayer_[0]->GetPlayerPos(),0);
	XMFLOAT3 camPos = Trans_P.position_;
	camPos.y += 5;
	camPos.z -= 10;
	pCamera_->SetPosition(camPos,0);

}

void PlayScene::Update()
{

//	GameObject* dbgTest = FindObject("SceneManager");
	if (Input::IsKey(DIK_SPACE)) {

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
