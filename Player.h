#pragma once
#include "Engine/GameObject.h"

//�v���C���[���Ǘ�����N���X
class Player : public GameObject
{
	int hModel_;	//���f���ԍ�
	int camType_;	
	XMFLOAT3 move_;
public:
	//�R���X�g���N�^
	Player(GameObject* parent);

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

	void PlayerMove();
};

