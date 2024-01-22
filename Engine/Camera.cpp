#include "Camera.h"

//変数
XMVECTOR position_[2];	//カメラの位置（視点）
XMVECTOR target_[2];	//見る位置（焦点）
XMMATRIX viewMatrix_[2];	//ビュー行列
XMMATRIX projMatrix_;	//プロジェクション行列


//初期化
void Camera::Initialize()
{
	position_[0] = XMVectorSet(0, 3, -20, 0);	//カメラの位置
	target_[0] = XMVectorSet(0, 0, 0, 0);	//カメラの焦点
	position_[1] = XMVectorSet(0, 6, -20, 0);	//カメラの位置
	target_[1] = XMVectorSet(0, 0, 0, 0);	//カメラの焦点
	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//更新
void Camera::Update()
{
	//ビュー行列の作成dddddd
	viewMatrix_[0] = XMMatrixLookAtLH(position_[0], target_[0], XMVectorSet(0, 1, 0, 0));
	viewMatrix_[1] = XMMatrixLookAtLH(position_[1], target_[1], XMVectorSet(0, 1, 0, 0));
}

//位置を設定
void Camera::SetPosition(XMVECTOR position, int type)
{
	position_[type] = position;
}

void Camera::SetPosition(XMFLOAT3 position, int type)
{
	SetPosition(XMLoadFloat3(&position), type);
}

//焦点を設定
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

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix(int type)
{
	return viewMatrix_[type];
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}