#pragma once
//�C���N���[�h
#include "Engine/GameObject.h"
class GameOverScene : public GameObject
{
public:
	GameOverScene(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

