#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
class Camera
{
private:
	XMFLOAT3 lightPos_;
	ID3D11Buffer* pCB_;
public:
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update(int _CamPos);

	void IntConstantBuffer(int _type);

	//▼セッター・ゲッター
	void SetPosition(XMVECTOR _position,int _type);
	void SetPosition(XMFLOAT3 _position,int _type);
	void SetTarget(XMVECTOR _target,int _type);
	void SetTarget(XMFLOAT3 _target,int _type);
	XMVECTOR GetPosition(int _type);
	XMVECTOR GetTarget(int _type);
	XMFLOAT3 GetLightPos() { return(lightPos_); }
	XMMATRIX GetViewMatrix();											//ビュー行列を取得
	XMMATRIX GetProjectionMatrix();										//プロジェクション行列を取得
};