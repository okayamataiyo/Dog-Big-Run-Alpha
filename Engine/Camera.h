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
	XMFLOAT4 lightSourcePosition_;
	ID3D11Buffer* pCB_;
public:
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update(int _CamPos);

	void IntConstantBuffer(int _type);

	//▼セッター・ゲッター
	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position,int type);
	void SetPosition(XMFLOAT3 position,int type);
	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target,int type);
	void SetTarget(XMFLOAT3 target,int type);
	void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
	XMVECTOR GetEyePosition(int _type);
	XMVECTOR GetTarget(int _type);
	XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }
	XMMATRIX GetViewMatrix();											//ビュー行列を取得
	XMMATRIX GetProjectionMatrix();										//プロジェクション行列を取得
};