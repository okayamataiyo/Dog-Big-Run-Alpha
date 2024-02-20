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

//���C�L���X�g�\����
struct RayCastData
{
	XMFLOAT3 start;		//���C���ˈʒu
	XMFLOAT3 dir;		//���C�̌����x�N�g��
	float	 dist;		//�Փ˓_�܂ł̋���
	BOOL	 hit;		//���C������������
	XMFLOAT3 normal;	//�@��

	RayCastData() { dist = 99999.0f; }
};

/// <summary>
/// FBX�t�@�C���������N���X
/// �قƂ�ǂ̏����͊e�p�[�c�����Ƃ�FbxParts�N���X�ōs��
/// </summary>
class Fbx
{
	//FbxParts�N���X���t�����h�N���X�ɂ���
	//FbxParts��private�Ȋ֐��ɂ��A�N�Z�X��
	friend class FbxParts;

	vector<FbxParts*> parts_;			//���f���̊e�p�[�c(�������邩��)

	FbxManager* pFbxManager_;		//FBX�t�@�C���������@�\�̖{��
	FbxScene* pFbxScene_;			//FBX�t�@�C���̃V�[��(Maya�ō�����S�Ă̕���)������
	FbxTime::EMode _frameRate;		//�A�j���[�V�����̃t���[�����[�g
	float _animSpeed;				//�A�j���[�V�������x
	int _startFrame, _endFrame;		//�A�j���[�V�����̍ŏ��ƍŌ�̃t���[��

	/// <summary>
	/// �m�[�h�̒��g�𒲂ׂ�
	/// </summary>
	/// <param name="_pNode">���ׂ�m�[�h</param>
	/// <param name="_pPartsList">�p�[�c�̃��X�g</param>
	void CheckNode(FbxNode* _pNode, vector<FbxParts*>* _pPartsList);

public:
	//�����o�֐�
	Fbx();
	~Fbx();
	HRESULT Load(string _fileName);
	void Draw(Transform& _transform,int _frame);
	void Release();

	/// <summary>
	/// �C�ӂ̃{�[���̈ʒu���擾
	/// </summary>
	/// <param name="_boneName">�擾�������{�[���̈ʒu</param>
	/// <returns>�{�[���̈ʒu</returns>
	XMFLOAT3 GetBonePosition(string _boneName);
	
	/// <summary>
	/// ���C�L���X�g(���C���΂��ē����蔻��)
	/// </summary>
	/// <param name="data">�K�v�Ȃ��̂��܂Ƃ߂��f�[�^</param>
	void RayCast(RayCastData* _data);
};

