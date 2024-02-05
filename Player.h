#pragma once
//インクルード
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

/// <summary>
/// プレイヤーを管理するクラス
/// </summary>
class Player : public GameObject
{
public:
	enum PLYAERS
	{
		PlayerFirst = 0,
		PlayerSeconds
	};

	enum GAMESTATE
	{
		WAIT = 0,
		WALK,
		RUN,
		JUNMP,

	}GameSta_;

	enum STATE
	{
		READY = 0,
		PLAY,
		GAMEOVER,
	}State_;

	int playerNum_;
	int hModel_;	//モデル番号
	int camType_;
	float powerY_;

	Transform transPlayer_;
	SphereCollider* pCollision_;
	//▼ゲームの演出で使うメンバ関数
	int TimeCounter_;
	
	//▼向き変えで使うメンバ変数
	XMVECTOR vecMove_;
	XMVECTOR vecLength_;
	float length_;
	XMVECTOR vecFront_;
	XMVECTOR vecDot_;
	float dot_;
	float angle_;
	XMVECTOR vecCross_;
	//▼ジャンプで使うメンバ変数
	bool  jumpFlg_;
	float rayDist_;		//地面とプレイヤーの差分
	float moveYTemp_;	//y座標をPrevに保存する
	float moveYPrev_;	//y座標を保存しておく

	//▼慣性で使うメンバ変数
	float mv;			//加速度
	XMFLOAT3 velocity_;	//速度

public:

	/// <summary>
	/// コンストラクタ関数
	/// </summary>
	/// <param name="_parent">親の名前</param>
	Player(GameObject* _parent);

	/// <summary>
	/// デストラクタ関数
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;

	void UpdateReady();
	void UpdatePlay();
	void UpdateGameOver();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 開放関数
	/// </summary>
	void Release() override;

	/// <summary>
	/// 何かに当たった時の関数
	/// </summary>
	/// <param name="_pTarget">当たった相手</param>
	void OnCollision(GameObject* _pTarget) override;

	/// <summary>
	/// プレイヤーの移動関数
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// プレイヤーのジャンプ関数
	/// </summary>
	void PlayerJump();

	/// <summary>
	/// プレイヤーの重力関数
	/// </summary>
	void PlayerGravity();

	//▼セッター・ゲッター
	/// <summary>
	/// プレイヤーの位置取得
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	Transform GetPlayerPos() { return transform_; }

	void SetTransform(XMFLOAT3 _position) { transform_.position_ = _position; }
};

