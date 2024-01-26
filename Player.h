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

//�v���C���[���Ǘ�����N���X
class Player : public GameObject
{
protected:
	int playerNum_;
	int hModel_[2];	//���f���ԍ�
	int camType_;	
	float powerX_[2];
	float powerY_[2];
	float powerZ_[2];
	//���W�����v�Ŏg�������o�ϐ�
	bool  jumpFlg_[2];
	float rayDist_[2];		//�n�ʂƃv���C���[�̍���
	float moveYTemp_[2];	//y���W��Prev�ɕۑ�����
	float moveYPrev_[2];	//y���W��ۑ����Ă���

	//�������Ŏg�������o�ϐ�
	float mv[2];			//�����x
	XMFLOAT3 velocity_[2];		//���x

	Transform TransPlayer_[2];
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
	/// <param name="_PlayerNum">�v���C���[�̔ԍ�</param>
	void PlayerJump(int _PlayerNum);

	//�Z�b�^�[�E�Q�b�^�[
	/// <summary>
	/// �v���C���[�̈ʒu�擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	Transform GetPlayerPos(int _PPos) { return TransPlayer_[_PPos]; }
};

