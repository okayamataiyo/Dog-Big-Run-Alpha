#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"
class Camera;
extern Camera* pCamera;
enum
{
	PlayerFirst,
	PlayerSeconds
};

//プレイヤーを管理するクラス
class Player : public GameObject
{
protected:
	int hModel_[2];	//モデル番号
	int camType_;	
	float powerX_[2];
	float powerY_[2];
	float powerZ_[2];
	bool  jumpFlg_;
	float moveYPrev_;
	XMFLOAT3 move_;
	Transform TransPlayer_[2];
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

