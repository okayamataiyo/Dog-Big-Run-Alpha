#include "Rootjob.h"
#include "SceneManager.h"

Rootjob::Rootjob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
}

Rootjob::~Rootjob()
{
}

void Rootjob::Initialize(void)
{
	Instantiate<SceneManager>(this);
	/*PlayScene* pPlayScene;
	pPlayScene = new PlayScene(this);

	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);
	Instantiate<PlayScene>(this);*/
}

void Rootjob::Update()
{
}

void Rootjob::Draw()
{
	/*for (auto& e : childList_)
		e->Draw();*/
}

void Rootjob::Release()
{
}
