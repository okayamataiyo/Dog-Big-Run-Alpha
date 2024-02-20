#pragma once
//インクルード
#include<d3d11.h>
#include<DirectXMath.h>
#include<DirectXTex.h>
#include<d3dcompiler.h>
#include<wincodec.h>
#include<string>
#include<wrl.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"LibFbxSDK-MD.lib")
#pragma comment(lib,"LibXml2-MD.lib")
#pragma comment(lib,"zlib-MD.lib")
#pragma comment( lib, "WindowsCodecs.lib" )

using namespace DirectX;
using namespace Microsoft::WRL;
using std::string;

/// <summary>
/// テクスチャ関連を扱うクラス
/// </summary>
class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	XMFLOAT2 imgSize_;
public:
	Texture();
	~Texture();
	HRESULT Load(string _fileName);
	void Release();
	ID3D11SamplerState* GetSampler() { return pSampler_; }	//サンプラーの取得
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }	//シェーダーリソースビューの取得
	XMFLOAT2 GetSize() { return imgSize_; }					//画像サイズの取得
};

