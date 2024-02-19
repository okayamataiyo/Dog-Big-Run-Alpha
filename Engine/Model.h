#pragma once
//�C���N���[�h
#include<string>
#include<vector>
#include"Transform.h"
#include"Fbx.h"

/// <summary>
/// 3D���f��(FBX�t�@�C��)���Ǘ�����
/// </summary>
namespace Model
{
	/// <summary>
	/// ���f�����
	/// </summary>
	struct ModelData
	{
		string fileName_;

		Fbx* pFbx_;

		Transform transform_;

		float nowFrame_, animSpeed_;
		int startFrame_, endFrame_;

		ModelData() :pFbx_(nullptr), nowFrame_(0), startFrame_(0), endFrame_(0), animSpeed_(0)
		{

		}

		void SetAnimFrame(int _start, int _end, float _speed)
		{
			nowFrame_ = (float)_start;
			startFrame_ = _start;
			endFrame_ = _end;
			animSpeed_ = _speed;
		}
	};
	void Initialize();
	int Load(std::string _fileName);
	void SetTransform(int _hModel, Transform _transform);
	void Draw(int _hModel);
	void Release(int _hModel);
	void AllRelease();



	/// <summary>
	/// ���C�L���X�g(���C���΂��ē����蔻��)
	/// </summary>
	/// <param name="handle">���肵�������f���̔ԍ�</param>
	/// <param name="data">�K�v�Ȃ��̂��܂Ƃ߂��f�[�^</param>
	void RayCast(int _handle, RayCastData* _data);
};