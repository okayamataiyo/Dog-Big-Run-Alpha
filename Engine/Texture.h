#pragma once
//�C���N���[�h
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
/// �e�N�X�`���֘A�������N���X
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
	ID3D11SamplerState* GetSampler() { return pSampler_; }	//�T���v���[�̎擾
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }	//�V�F�[�_�[���\�[�X�r���[�̎擾
	XMFLOAT2 GetSize() { return imgSize_; }					//�摜�T�C�Y�̎擾
};

