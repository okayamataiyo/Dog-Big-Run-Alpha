#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
class Camera
{
private:
	XMFLOAT4 lightSourcePosition_;
	ID3D11Buffer* pCBStageScene_;
public:
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update(int _CamPos);

	void IntConstantBuffer(int _type);

	//���Z�b�^�[�E
	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position,int type);
	void SetPosition(XMFLOAT3 position,int type);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target,int type);
	void SetTarget(XMFLOAT3 target,int type);
	void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
	XMVECTOR GetEyePosition(int _type);
	XMVECTOR GetTarget(int _type);
	XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }

	//�r���[�s����擾
	XMMATRIX GetViewMatrix(int type);

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();
};