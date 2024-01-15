#include "SceneManager.h"
#include "Model.h"
#include "../TestScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{

	//シーンを実際に切り替える
	//現在のシーンと、ネクストシーンが別だったら切り替え
	if (currentSceneID_ != nextSceneID_) {

		//そのシーンのオブジェクトを全削除
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//ロードしたデータを全削除
		Model::Release();
		//後片付け終了
		switch (nextSceneID_) {

		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
	//現在のシーンの後片付け
	//新しいシーンの準備
	//currentSceneID_をnextSCENEID
	
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// 次に指定したシーンをnextSceneID_に設定する(=次のUpdateでシーンが変わる)
/// </summary>
/// <param name="_next">次のシーン</param>
void SceneManager::ChangeScene(SCENE_ID _next)
{

	nextSceneID_ = _next;
}
