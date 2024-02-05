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
	float length_;
	XMVECTOR vecFront_;
	XMVECTOR vecDot_;
	float dot_;
	float angle_;
	XMVECTOR vecCross_;
	//���W�����v�Ŏg�������o�ϐ�
	bool  jumpFlg_;
	float rayDist_;		//�n�ʂƃv���C���[�̍���
	float moveYTemp_;	//y���W��Prev�ɕۑ�����
	float moveYPrev_;	//y���W��ۑ����Ă���

	//�������Ŏg�������o�ϐ�
	float mv;			//�����x
	XMFLOAT3 velocity_;	//���x

public:

	/// <summary>
	/// �R���X�g���N�^�֐�
	/// </summary>
	/// <param name="_parent">�e�̖��O</param>
	Player(GameObject* _parent);

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
	/// �v���C���[�̏d�͊֐�
	/// </summary>
	void PlayerGravity();

	//���Z�b�^�[�E�Q�b�^�[
	/// <summary>
	/// �v���C���[�̈ʒu�擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	Transform GetPlayerPos() { return transform_; }

	void SetTransform(XMFLOAT3 _position) { transform_.position_ = _position; }
};

