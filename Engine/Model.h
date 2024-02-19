#pragma once
//インクルード
#include<string>
#include<vector>
#include"Transform.h"
#include"Fbx.h"

/// <summary>
/// 3Dモデル(FBXファイル)を管理する
/// </summary>
namespace Model
{
	/// <summary>
	/// モデル情報
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
	/// レイキャスト(レイを飛ばして当たり判定)
	/// </summary>
	/// <param name="handle">判定したいモデルの番号</param>
	/// <param name="data">必要なものをまとめたデータ</param>
	void RayCast(int _handle, RayCastData* _data);
};