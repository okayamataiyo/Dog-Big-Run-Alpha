#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
class Camera
{
public:
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position,int type);
	void SetPosition(XMFLOAT3 position,int type);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target,int type);
	void SetTarget(XMFLOAT3 target,int type);

	XMVECTOR GetEyePosition(int type);

	//ビュー行列を取得
	XMMATRIX GetViewMatrix(int type);

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();
};