#pragma once
//インクルード
#include <fbxsdk.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

using namespace DirectX;

class Fbx;
struct RayCastData;

/// <summary>
/// FBXの1つのパーツを扱うクラス
/// </summary>
class FbxParts
{
private:
	Camera* pCamera;

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

	/// <summary>
	/// マテリアル情報(質感の情報)
	/// </summary>
	struct MATERIAL
	{
		DWORD    polygonCount;		 //マテリアルのポリゴン数
		XMFLOAT4 diffuse;			 //拡散反射光への反射強度
		XMFLOAT4 ambient;			 //環境光への反射強度
		XMFLOAT4 specular;			 //鏡面反射光への反射強度
		float    shininess;			 //ハイライトの強さ(サイズ)
		Texture* pTexture;			 //テクスチャ
	}*pMaterial_;

	/// <summary>
	/// ボーン構造体(関節情報)
	/// </summary>
	struct Bone
	{
		XMMATRIX bindPose;			 //初期ポーズ時のボーン変換行列
		XMMATRIX newPose;			 //アニメーションで変化した時のボーン変換行列
		XMMATRIX diffPose;			 //mBindPoseに対するmNorPoseの変化量
	};

	/// <summary>
	/// ウェイト構造体(ボーンと頂点の関連付け)
	/// </summary>
	struct Weight
	{
		XMFLOAT3 posOrigin;			  //元々の頂点座標
		XMFLOAT3 normalOrigin;		  //元々の法線ベクトル
		int* pBoneIndex;			  //関連するボーンのID
		float* pBoneWeight;			  //ボーンの重み
	};

	//各データの個数
	DWORD vertexCount_;				  //頂点数
	DWORD polygonCount_;			  //ポリゴン数
	DWORD indexCount_;				  //インデックス数
	DWORD materialCount_;			  //マテリアルの個数
	DWORD polygonVertexCount_;		  //ポリゴン頂点インデックス数

	VERTEX* pVertexData_;
	DWORD** ppIndexData_;

	ID3D11Buffer* pVertexBuffer_;

	ID3D11Buffer** ppIndexBuffer_ = NULL;

	ID3D11Buffer* pConstantBuffer_;

	FbxSkin* pSkinInfo_;
	FbxCluster** ppCluster_;
	int numBone_;
	Bone* pBoneArray_;
	Weight* pWeightArray_;

	void InitVertex(fbxsdk::FbxMesh* _mesh);
	void InitMaterial(fbxsdk::FbxNode* _pNode);
	void InitTexture(fbxsdk::FbxSurfaceMaterial* _pMaterial, const DWORD& _i);
	void InitIndex(fbxsdk::FbxMesh* _pMesh);
	void InitSkelton(FbxMesh* _pMesh);
	void InitConstantBuffer();

public:
	FbxParts(Camera* _camera) : pCamera(_camera){}
	FbxParts();
	~FbxParts();

	/// <summary>
	/// FBXファイルから情報をロードして諸々準備する
	/// </summary>
	/// <param name="_pNode">情報が入っているノード</param>
	/// <returns>結果</returns>
	HRESULT Init(FbxNode* _pNode);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="_transform">ワールド行列</param>
	void Draw(Transform& _transform);

	void DrawSkinAnime(Transform& _transform, FbxTime _time);

	void DrawMeshAnime(Transform& _transform, FbxTime _time, FbxScene* _scene);

	bool GetBonePosition(std::string _boneName, XMFLOAT3* _position);

	/// <summary>
	/// スキンメッシュ情報を取得
	/// </summary>
	/// <returns>スキンメッシュ情報</returns>
	FbxSkin* GetSkinInfo() { return pSkinInfo_; }

	/// <summary>
	/// レイキャスト(レイを飛ばして当たり判定)
	/// </summary>
	/// <param name="_data">必要なものをまとめたデータ</param>
	void RayCast(RayCastData* _data);
};

