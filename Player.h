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
	int hModel_[2];	//���f���ԍ�
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

