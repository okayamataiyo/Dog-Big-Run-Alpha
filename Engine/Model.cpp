#include "Model.h"
#include "Direct3D.h"
#include "../Global.h"

namespace Model
{
	//モデルのポインタをぶち込んでおくベクタ
	vector<ModelData* >modelList;

	void Initialize()
	{
		AllRelease();
	}

	int Model::Load(string _fileName)
	{
		ModelData* pData;
		pData = new ModelData;
		bool isExist = false;
		for (int i = 0; i < modelList.size(); i++)
		{
			if (modelList[i] != nullptr && modelList[i]->fileName_ == _fileName)
			{
				pData->pFbx_ = pData->pFbx_;
				isExist = true;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->pFbx_ = new Fbx;
			if (FAILED(pData->pFbx_->Load(_fileName)))
			{
				//開けなかった
				SAFE_DELETE(pData->pFbx_);
				SAFE_DELETE(pData);
				return -1;
			}

			//無事開けた
			pData->fileName_ = _fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < modelList.size(); i++)
		{
			if (modelList[i] == nullptr)
			{
				modelList[i] = pData;
				return i;
			}
		}

		//新たに追加
		modelList.push_back(pData);
		return (int)modelList.size() - 1;
	}

	void Model::SetTransform(int _hModel, Transform _transform)
	{
		//モデル番号は、modelListのインデックス
		modelList[_hModel]->transform_ = _transform;

	}

	void Model::Draw(int _hModel)
	{
		//モデル番号は、modelListのインデックス
		if (_hModel < 0 || _hModel >= modelList.size() || modelList[_hModel] == nullptr)
		{
			return;
		}

		modelList[_hModel]->nowFrame_ += modelList[_hModel]->animSpeed_;

		if (modelList[_hModel]->nowFrame_ > (float)modelList[_hModel]->endFrame_)
		{
			modelList[_hModel]->nowFrame_ = (float)modelList[_hModel]->startFrame_;
		}

		if (modelList[_hModel]->pFbx_)
		{
			modelList[_hModel]->pFbx_->Draw(modelList[_hModel]->transform_, (int)modelList[_hModel]->nowFrame_);
		}
	}

	void Model::Release(int _hModel)
	{
		if (_hModel < 0 || _hModel >= modelList.size() || modelList[_hModel] == nullptr)
		{
			return;
		}

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < modelList.size(); i++)
		{
			//すでに開いている場合
			if (modelList[i] != nullptr && i != _hModel && modelList[i]->pFbx_ == modelList[_hModel]->pFbx_)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false)
		{
			SAFE_DELETE(modelList[_hModel]->pFbx_);
		}


		SAFE_DELETE(modelList[_hModel]);
	}

	void AllRelease()
	{
		for (int i = 0; i < modelList.size(); i++)
		{
			if (modelList[i] != nullptr)
			{
				Release(i);
			}
		}
		modelList.clear();
	}

	void Model::RayCast(int _handle, RayCastData* _data)
	{
		XMFLOAT3 target = Transform::Float3Add(_data->start, _data->dir);
		XMMATRIX matInv = XMMatrixInverse(nullptr, modelList[_handle]->transform_.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&_data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = vecTarget - vecStart;

		XMStoreFloat3(&_data->start, vecStart);
		XMStoreFloat3(&_data->dir, vecDir);

		modelList[_handle]->pFbx_->RayCast(_data);
	}
}