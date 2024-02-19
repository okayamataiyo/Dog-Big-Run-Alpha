#pragma once
//�C���N���[�h
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
/// FBX��1�̃p�[�c�������N���X
/// </summary>
class FbxParts
{
private:
	Camera* pCamera;

	/// <summary>
	/// 1�̒��_�����i�[����\����
	/// </summary>
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 uv;
	};

	/// <summary>
	/// �R���X�^���g�o�b�t�@�[
	/// GPU(�V�F�[�_�[��)�֑��鐔�l���܂Ƃ߂��\����
	/// Simple3D.hlsl�̃O���[�o���ϐ��ƑΉ�������
	/// </summary>
	struct CONSTANT_BUFFER
	{
		XMMATRIX worldVewProj;		//���[���h�A�r���[�A�v���W�F�N�V�����s��̍���(���_�ϊ��Ɏg�p)
		XMMATRIX normalTrans;		//��]�s��Ɗg��s��̋t�s���������������(�@���̕ό`�Ɏg�p)
		XMMATRIX world;				//���[���h�s��
		XMFLOAT4 lightDirection;	//���C�g�̌���
		XMFLOAT4 diffuse;			//�g�U���ˌ��A�}�e���A���̐F(�e�N�X�`���\���Ă鎞�͎g��Ȃ�)
		XMFLOAT4 ambient;			//����
		XMFLOAT4 speculer;			//���ʔ��ˌ�(Lambert�̏ꍇ��0)
		XMFLOAT4 cameraPosition;	//�J�����̈ʒu(�n�C���C�g�̌v�Z�ɕK�v)
		FLOAT    shininess;			//�n�C���C�g�̋���(Maya��CosinePower)
		BOOL     isTexture;			//�e�N�X�`���̗L��
	};

	/// <summary>
	/// �}�e���A�����(�����̏��)
	/// </summary>
	struct MATERIAL
	{
		DWORD    polygonCount;		 //�}�e���A���̃|���S����
		XMFLOAT4 diffuse;			 //�g�U���ˌ��ւ̔��ˋ��x
		XMFLOAT4 ambient;			 //�����ւ̔��ˋ��x
		XMFLOAT4 specular;			 //���ʔ��ˌ��ւ̔��ˋ��x
		float    shininess;			 //�n�C���C�g�̋���(�T�C�Y)
		Texture* pTexture;			 //�e�N�X�`��
	}*pMaterial_;

	/// <summary>
	/// �{�[���\����(�֐ߏ��)
	/// </summary>
	struct Bone
	{
		XMMATRIX bindPose;			 //�����|�[�Y���̃{�[���ϊ��s��
		XMMATRIX newPose;			 //�A�j���[�V�����ŕω��������̃{�[���ϊ��s��
		XMMATRIX diffPose;			 //mBindPose�ɑ΂���mNorPose�̕ω���
	};

	/// <summary>
	/// �E�F�C�g�\����(�{�[���ƒ��_�̊֘A�t��)
	/// </summary>
	struct Weight
	{
		XMFLOAT3 posOrigin;			  //���X�̒��_���W
		XMFLOAT3 normalOrigin;		  //���X�̖@���x�N�g��
		int* pBoneIndex;			  //�֘A����{�[����ID
		float* pBoneWeight;			  //�{�[���̏d��
	};

	//�e�f�[�^�̌�
	DWORD vertexCount_;				  //���_��
	DWORD polygonCount_;			  //�|���S����
	DWORD indexCount_;				  //�C���f�b�N�X��
	DWORD materialCount_;			  //�}�e���A���̌�
	DWORD polygonVertexCount_;		  //�|���S�����_�C���f�b�N�X��

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
	/// FBX�t�@�C������������[�h���ď��X��������
	/// </summary>
	/// <param name="_pNode">��񂪓����Ă���m�[�h</param>
	/// <returns>����</returns>
	HRESULT Init(FbxNode* _pNode);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="_transform">���[���h�s��</param>
	void Draw(Transform& _transform);

	void DrawSkinAnime(Transform& _transform, FbxTime _time);

	void DrawMeshAnime(Transform& _transform, FbxTime _time, FbxScene* _scene);

	bool GetBonePosition(std::string _boneName, XMFLOAT3* _position);

	/// <summary>
	/// �X�L�����b�V�������擾
	/// </summary>
	/// <returns>�X�L�����b�V�����</returns>
	FbxSkin* GetSkinInfo() { return pSkinInfo_; }

	/// <summary>
	/// ���C�L���X�g(���C���΂��ē����蔻��)
	/// </summary>
	/// <param name="_data">�K�v�Ȃ��̂��܂Ƃ߂��f�[�^</param>
	void RayCast(RayCastData* _data);
};

