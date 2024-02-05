#pragma once
//インクルード
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "Engine/Texture.h"
#include "Engine/Transform.h"

using namespace DirectX;

/// <summary>
/// 2D画像を表示するためのクラス
/// </summary>
class Sprite
{
	//1つの頂点情報を格納する構造体
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 uv;
	};

	//コンスタントバッファー
	struct CB
	{
		XMMATRIX world;
		XMMATRIX uvTrans;
		XMFLOAT4 color;
	};

	ID3D11Buffer* pVertexBuffer_;

	ID3D11Buffer* pIndexBuffer_;

	Texture* pTexture_;

	ID3D11Buffer* pConstantBuffer_;


private:
	void InitVertex();
	void InitIndex();
	void InitConstantBuffer();

public:
	Sprite();
	~Sprite();

	HRESULT Load(std::string _fileName);

	void Draw(Transform& _transform, RECT _rect, float _alpha);

	XMFLOAT3 GetTextureSize() { return pTexture_->GetTextureSize(); }
};

