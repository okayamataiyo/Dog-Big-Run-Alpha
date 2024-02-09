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
	XMFLOAT3 lightPos_;
	ID3D11Buffer* pCB_;
public:
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update(int _CamPos);

	void IntConstantBuffer(int _type);

	//���Z�b�^�[�E�Q�b�^�[
	void SetPosition(XMVECTOR _position,int _type);
	void SetPosition(XMFLOAT3 _position,int _type);
	void SetTarget(XMVECTOR _target,int _type);
	void SetTarget(XMFLOAT3 _target,int _type);
	XMVECTOR GetPosition(int _type);
	XMVECTOR GetTarget(int _type);
	XMFLOAT3 GetLightPos() { return(lightPos_); }
	XMMATRIX GetViewMatrix();											//�r���[�s����擾
	XMMATRIX GetProjectionMatrix();										//�v���W�F�N�V�����s����擾
};