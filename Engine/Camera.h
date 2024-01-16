#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
class Camera
{
public:
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position,int type);
	void SetPosition(XMFLOAT3 position,int type);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target,int type);
	void SetTarget(XMFLOAT3 target,int type);

	XMVECTOR GetEyePosition(int type);

	//�r���[�s����擾
	XMMATRIX GetViewMatrix(int type);

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();
};