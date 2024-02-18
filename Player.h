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
//	float powerY_;

	Transform transPlayer_;
	Camera camera_;
	SphereCollider* pCollision_;
	//▼ゲームの演出で使うメンバ関数
	int TimeCounter_;
	
	//▼向き変えで使うメンバ変数
	XMVECTOR vecMove_;
	XMVECTOR vecLength_;
	XMVECTOR vecFront_;
	XMVECTOR vecDot_;
	XMVECTOR vecCross_;
	float length_;
	float dot_;
	float angle_;
	//▼ジャンプで使うメンバ変数
	bool  jumpFlg_;
	int hStageModel_[2];
	float rayGravityDist_;		//地面とプレイヤーの差分
	float moveYTemp_;	//y座標をPrevに保存する
	float moveYPrev_;	//y座標を保存しておく

	//▼すり抜け床で使うメンバ変数
	int isFloor_;		//すり抜け床にレイを飛ばしているかどうか
	int prevIsFloor_;	//1フレーム前にisFloorフラグがどうなっていたか
	float rayUpDist_;	//上の物体とプレイヤーの差分
	float rayDownDist_;	//下のすり抜けたい物体とプレイヤーの差分

	//▼慣性で使うメンバ変数
	float mv;			//加速度
	XMFLOAT3 velocity_;	//速度

	//▼壁判定で使うメンバ変数
	float rayWallDist_;

public:

	/// <summary>
	/// コンストラクタ関数
	/// </summary>
	/// <param name="_parent">親の名前</param>
	Player(GameObject* _pParent);

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
	/// プレイヤーの壁めり込み防止関数
	/// </summary>
	void PlayerWall();

	/// <summary>
	/// プレイヤーの重力関数
	/// </summary>
	void PlayerGravity();

	XMVECTOR GetVecPos() { return XMLoadFloat3(&transform_.position_); }
};

