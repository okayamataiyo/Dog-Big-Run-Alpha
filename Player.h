#pragma once
#include "Engine/GameObject.h"

//�v���C���[���Ǘ�����N���X
class Player : public GameObject
{
protected:
	int hModel_;	//���f���ԍ�
	int camType_;	
	XMFLOAT3 move_;
	Transform TransPlayer_;
public:
	//�R���X�g���N�^
	Player(GameObject* _parent);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �v���C���[�̈ړ��֐�
	/// </summary>
	void PlayerMove();

	//�Z�b�^�[�E�Q�b�^�[
	/// <summary>
	/// �v���C���[�̈ʒu�擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	Transform GetPlayerPos() { return TransPlayer_; }
};

