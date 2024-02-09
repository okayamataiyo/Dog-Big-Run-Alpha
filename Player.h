#pragma once
//�C���N���[�h
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

/// <summary>
/// �v���C���[���Ǘ�����N���X
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
	int hModel_;	//���f���ԍ�
	int camType_;
	float powerY_;

	Transform transPlayer_;
	SphereCollider* pCollision_;
	//���Q�[���̉��o�Ŏg�������o�֐�
	int TimeCounter_;
	
	//�������ς��Ŏg�������o�ϐ�
	XMVECTOR vecMove_;
	XMVECTOR vecLength_;
	XMVECTOR vecFront_;
	XMVECTOR vecDot_;
	XMVECTOR vecCross_;
	float length_;
	float dot_;
	float angle_;
	//���W�����v�Ŏg�������o�ϐ�
	bool  jumpFlg_;
	float rayDist_;		//�n�ʂƃv���C���[�̍���
	float moveYTemp_;	//y���W��Prev�ɕۑ�����
	float moveYPrev_;	//y���W��ۑ����Ă���

	//�������Ŏg�������o�ϐ�
	float mv;			//�����x
	XMFLOAT3 velocity_;	//���x

	//���ǔ���Ŏg�������o�ϐ�
	XMVECTOR velocity2_;
	XMFLOAT3 next_;
	XMVECTOR ipVec_;
	XMVECTOR push_;
	XMVECTOR th_;

public:

	/// <summary>
	/// �R���X�g���N�^�֐�
	/// </summary>
	/// <param name="_parent">�e�̖��O</param>
	Player(GameObject* _pParent);

	/// <summary>
	/// �f�X�g���N�^�֐�
	/// </summary>
	~Player();

	/// <summary>
	/// �������֐�
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;

	void UpdateReady();
	void UpdatePlay();
	void UpdateGameOver();

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �J���֐�
	/// </summary>
	void Release() override;

	/// <summary>
	/// �����ɓ����������̊֐�
	/// </summary>
	/// <param name="_pTarget">������������</param>
	void OnCollision(GameObject* _pTarget) override;

	/// <summary>
	/// �v���C���[�̈ړ��֐�
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// �v���C���[�̃W�����v�֐�
	/// </summary>
	void PlayerJump();

	/// <summary>
	/// �v���C���[�̕ǂ߂荞�ݖh�~�֐�
	/// </summary>
	void PlayerWall();

	/// <summary>
	/// �v���C���[�̏d�͊֐�
	/// </summary>
	void PlayerGravity();
	Transform GetPlayerPos() { return transform_; }
	//void SetTransform(XMFLOAT3 _position) { transform_.position_ = _position; }
};

