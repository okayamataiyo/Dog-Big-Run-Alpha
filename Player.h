#pragma once
#include "Engine/GameObject.h"

//プレイヤーを管理するクラス
class Player : public GameObject
{
protected:
	int hModel_;	//モデル番号
	int camType_;	
	XMFLOAT3 move_;
	Transform Trans_P;
public:
	//コンストラクタ
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void PlayerMove();
};

