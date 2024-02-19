#pragma once
//インクルード
#include <fbxsdk.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

class Fbx;
struct RayCastData;

/// <summary>
/// FBXの1つのパーツを扱うクラス
/// </summary>
class FbxParts
{
	/// <summary>
	/// 1つの頂点情報を格納する構造体
	/// </summary>
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 uv;
	};

	/// <summary>
	/// コンスタントバッファー
	/// GPU(シェーダー側)へ送る数値をまとめた構造体
	/// Simple3D.hlslのグローバル変数と対応させる
	/// </summary>
	struct CONSTANT_BUFFER
	{
		XMMATRIX worldVewProj;		//ワールド、ビュー、プロジェクション行列の合成(頂点変換に使用)
		XMMATRIX normalTrans;		//回転行列と拡大行列の逆行列を合成したもの(法線の変形に使用)
		XMMATRIX world;				//ワールド行列
		XMFLOAT4 lightDirection;	//ライトの向き
		XMFLOAT4 diffuse;			//拡散反射光、マテリアルの色(テクスチャ貼ってる時は使わない)
		XMFLOAT4 ambient;			//環境光
		XMFLOAT4 speculer;			//鏡面反射光(Lambertの場合は0)
		XMFLOAT4 cameraPosition;	//カメラの位置(ハイライトの計算に必要)
		FLOAT    shininess;			//ハイライトの強さ(MayaのCosinePower)
		BOOL     isTexture;			//テクスチャの有無
	};

	struct MATERIAL
	{
		DWORD    polygonCount;		 //マテリアルのポリゴン数
		XMFLOAT4 diffuse;			 //拡散反射光への反射強度
		XMFLOAT4 ambient;			 //環境光への反射強度
		XMFLOAT4 specular;			 //鏡面反射光への反射強度
		float    shininess;			 //ハイライトの強さ(サイズ)
		Texture* pTexture;			 //テクスチャ
	}*pMaterial_;
};

