#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

using namespace DirectX;


enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_TOON,
	SHADER_TOONOUTLINE,
	SHADER_MAX,
};

namespace Direct3D
{

	extern ID3D11Device* pDevice_;		                //�f�o�C�X
	extern ID3D11DeviceContext* pContext_;		        //�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();
	HRESULT InitShaderToon();
	HRESULT InitShaderToonOutLine();

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

	/// <summary>
	/// �O�p�`�Ɛ���(���C)�̏Փ˔���(�Փ˔���Ɏg�p)
	/// </summary>
	/// <param name="_start">���C�̃X�^�[�g�ʒu</param>
	/// <param name="_direction">���C�̕���</param>
	/// <param name="_v0">�O�p�`�̊e���_�ʒu</param>
	/// <param name="_v1">�O�p�`�̊e���_�ʒu</param>
	/// <param name="_v2">�O�p�`�̊e���_�ʒu</param>
	/// <param name="_distance">�Փ˓_�܂ł̋�����Ԃ�</param>
	/// <returns>�Փ˂������ǂ���</returns>
	bool Intersect(XMFLOAT3& _start, XMFLOAT3& _direction,XMFLOAT3& _v0,XMFLOAT3& _v1, XMFLOAT3& _v2, float* _distance);

	/// <summary>
	/// �r���[�|�[�g�ɏ�������
	/// </summary>
	/// <param name="VpType">�r���[�|�[�g�̎��</param>
	void SetViewPort(int VpType);

};

