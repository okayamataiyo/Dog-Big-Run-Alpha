#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <vector>
#include <string>
#include "Transform.h"
#include "Camera.h"

using std::vector;

class Texture;
class Camera;
class FbxParts;

extern Camera* pCamera;

//レイキャスト構造体
struct RayCastData
{
	XMFLOAT3 start;		//レイ発射位置
	XMFLOAT3 dir;		//レイの向きベクトル
	float	 dist;		//衝突点までの距離
	BOOL	 hit;		//レイが当たったか
	XMFLOAT3 normal;	//法線

	RayCastData() { dist = 99999.0f; }
};

/// <summary>
/// FBXファイルを扱うクラス
/// ほとんどの処理は各パーツ事ごとにFbxPartsクラスで行う
/// </summary>
class Fbx
{
	//FbxPartsクラスをフレンドクラスにする
	//FbxPartsのprivateな関数にもアクセス可
	friend class FbxParts;

	vector<FbxParts*> parts_;			//モデルの各パーツ(複数あるかも)

	FbxManager* pFbxManager_;		//FBXファイルを扱う機能の本体
	FbxScene* pFbxScene_;			//FBXファイルのシーン(Mayaで作った全ての物体)を扱う
	FbxTime::EMode _frameRate;		//アニメーションのフレームレート
	float _animSpeed;				//アニメーション速度
	int _startFrame, _endFrame;		//アニメーションの最初と最後のフレーム

	/// <summary>
	/// ノードの中身を調べる
	/// </summary>
	/// <param name="_pNode">調べるノード</param>
	/// <param name="_pPartsList">パーツのリスト</param>
	void CheckNode(FbxNode* _pNode, vector<FbxParts*>* _pPartsList);

public:
	//メンバ関数
	Fbx();
	~Fbx();
	HRESULT Load(string _fileName);
	void Draw(Transform& _transform,int _frame);
	void Release();

	/// <summary>
	/// 任意のボーンの位置を取得
	/// </summary>
	/// <param name="_boneName">取得したいボーンの位置</param>
	/// <returns>ボーンの位置</returns>
	XMFLOAT3 GetBonePosition(string _boneName);
	
	/// <summary>
	/// レイキャスト(レイを飛ばして当たり判定)
	/// </summary>
	/// <param name="data">必要なものをまとめたデータ</param>
	void RayCast(RayCastData* _data);
};

