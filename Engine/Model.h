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
	struct ModelData
	{
		string fileName;

		Fbx* pFbx;

		Transform transform;

		float nowFrame, animSpeed;
		int startFrame, endFrame;

		ModelData() :pFbx(nullptr), nowFrame(0), startFrame(0), endFrame(0), animSpeed(0)
		{

		}

		void SetAnimFrame(int _start, int _end, float _speed)
		{
			nowFrame = (float)_start;
			startFrame = _start;
			endFrame = _end;
			animSpeed = _speed;
		}
	};

	int Load(std::string _fileName);
	void SetTransform(int _hModel, Transform _transform);
	void Draw(int _hModel);
	void Release();

	/// <summary>
	/// レイキャスト(レイを飛ばして当たり判定)
	/// </summary>
	/// <param name="handle">判定したいモデルの番号</param>
	/// <param name="data">必要なものをまとめたデータ</param>
	void RayCast(int _handle, RayCastData* _data);
};