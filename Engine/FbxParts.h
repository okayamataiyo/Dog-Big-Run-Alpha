#pragma once
//�C���N���[�h
#include <fbxsdk.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

class Fbx;
struct RayCastData;

/// <summary>
/// FBX��1�̃p�[�c�������N���X
/// </summary>
class FbxParts
{
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

	struct MATERIAL
	{
		DWORD    polygonCount;		 //�}�e���A���̃|���S����
		XMFLOAT4 diffuse;			 //�g�U���ˌ��ւ̔��ˋ��x
		XMFLOAT4 ambient;			 //�����ւ̔��ˋ��x
		XMFLOAT4 specular;			 //���ʔ��ˌ��ւ̔��ˋ��x
		float    shininess;			 //�n�C���C�g�̋���(�T�C�Y)
		Texture* pTexture;			 //�e�N�X�`��
	}*pMaterial_;
};

