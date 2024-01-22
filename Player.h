#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

enum
{
	PlayerFirst,
	PlayerSeconds
};

//プレイヤーを管理するクラス
class Player : public GameObject
{
protected:
	int hModel_;	//モデル番号
	int camType_;	
	float powerX_;
	float powerY_;
	float powerZ_;
	XMFLOAT3 move_;
	Transform TransPlayer_[2];
	Camera* pCamera_;
public:
	int playerNum_;
	//コンストラクタ
	Player(GameObject* _parent);

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

	/// <summary>
	/// プレイヤーの移動関数
	/// </summary>
	void PlayerMove();

	//セッター・ゲッター
	/// <summary>
	/// プレイヤーの位置取得
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	Transform GetPlayerPos(int _PPos) { return TransPlayer_[_PPos]; }
};

