#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Camera.h"
/// <summary>
/// カメラのコントロールを管理するクラス
/// </summary>
class Controller : public GameObject
{
private:
	Player* pPlayer_[2];
	Camera* pCamera_;
	XMFLOAT3 camPos_[2];
public:
	Controller(GameObject* _pParent);
	~Controller();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	Player GetPlayer(int _type) { return pPlayer_[_type]; }
};

