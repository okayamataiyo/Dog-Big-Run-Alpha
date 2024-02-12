#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"
#include "PlayScene.h"
/// <summary>
/// カメラのコントロールを管理するクラス
/// </summary>
class Controller : public GameObject
{
private:
	Camera* pCamera_;
	PlayScene* pPlayScene_;
	XMFLOAT3 camPos_[2];
public:
	Controller(GameObject* _pParent);
	~Controller();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

