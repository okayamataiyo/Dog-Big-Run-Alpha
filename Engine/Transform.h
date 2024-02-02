#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform
{
public:
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
	XMFLOAT3 position_;		//位置
	XMFLOAT3 rotate_;		//向き
	XMFLOAT3 scale_;		//拡大率
	Transform* pParent_;	//親オブジェクトのTransform

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calclation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();

	//法線変形用行列を取得
	XMMATRIX GetNormalMatrix();

	static XMFLOAT3 Float3Add(XMFLOAT3 _a, XMFLOAT3 _b){return XMFLOAT3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);}
};