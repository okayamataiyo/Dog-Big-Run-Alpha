#include "Camera.h"

//�ϐ�
XMVECTOR position_[2];	//�J�����̈ʒu�i���_�j
XMVECTOR target_[2];	//����ʒu�i�œ_�j
XMMATRIX viewMatrix_[2];	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��


//������
void Camera::Initialize()
{
	position_[0] = XMVectorSet(0, 3, -20, 0);	//�J�����̈ʒu
	target_[0] = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	position_[1] = XMVectorSet(0, 6, -20, 0);	//�J�����̈ʒu
	target_[1] = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬dddddd
	viewMatrix_[0] = XMMatrixLookAtLH(position_[0], target_[0], XMVectorSet(0, 1, 0, 0));
	viewMatrix_[1] = XMMatrixLookAtLH(position_[1], target_[1], XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position, int type)
{
	position_[type] = position;
}

void Camera::SetPosition(XMFLOAT3 position, int type)
{
	SetPosition(XMLoadFloat3(&position), type);
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target, int type)
{
	target_[type] = target;
}

void Camera::SetTarget(XMFLOAT3 target, int type)
{
	SetTarget(XMLoadFloat3(&target), type);
}

XMVECTOR Camera::GetEyePosition(int type)
{
	return position_[type];
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix(int type)
{
	return viewMatrix_[type];
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}