#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

enum
{
	PlayerFirst,
	PlayerSeconds
};

//�v���C���[���Ǘ�����N���X
class Player : public GameObject
{
protected:
	int hModel_;	//���f���ԍ�
	int camType_;	
	float powerX_;
	float powerY_;
	float powerZ_;
	XMFLOAT3 move_;
	Transform TransPlayer_[2];
	Camera* pCamera_;
public:
	int playerNum_;
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
	Transform GetPlayerPos(int _PPos) { return TransPlayer_[_PPos]; }
};

