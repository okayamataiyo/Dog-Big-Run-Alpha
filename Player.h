#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"
class Camera;
extern Camera* pCamera;

//プレイヤーを管理するクラス
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
	float powerY_[2];
	//▼ゲームの演出で使うメンバ関数
	int TimeCounter_;
	
	//▼向き変えで使うメンバ変数
	XMVECTOR vecMove_[2];
	XMVECTOR vecLength_[2];
	float length_[2];
	XMVECTOR vecFront_[2];
	XMVECTOR vecDot_[2];
	float dot_[2];
	float angle_[2];
	XMVECTOR vecCross_[2];
	//▼ジャンプで使うメンバ変数
	bool  jumpFlg_[2];
	float rayDist_[2];		//地面とプレイヤーの差分
	float moveYTemp_[2];	//y座標をPrevに保存する
	float moveYPrev_[2];	//y座標を保存しておく

	//▼慣性で使うメンバ変数
	float mv[2];			//加速度
	XMFLOAT3 velocity_[2];	//速度

	Transform transPlayer_[2];
	BoxCollider* pCollision;
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

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 開放関数
	/// </summary>
	void Release() override;

	void UpdateReady();
	void UpdatePlay();
	void UpdateGameOver();

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
	/// <param name="_PlayerNum">プレイヤーの番号</param>
	void PlayerJump(int _PlayerNum);

	//セッター・ゲッター
	/// <summary>
	/// プレイヤーの位置取得
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	Transform GetPlayerPos(int _PPos) { return transPlayer_[_PPos]; }
};

