#include <assert.h>
#include "Fbx.h"
#include "Direct3D.h"
#include "FbxParts.h"

void Fbx::CheckNode(FbxNode* _pNode, vector<FbxParts*>* _pPartsList)
{
    //そのノードにはメッシュ情報が入っているだろうか？
    FbxNodeAttribute* attr = _pNode->GetNodeAttribute();
    if (attr != nullptr && attr->GetAttributeType() == FbxNodeAttribute::eMesh)
    {
        //パーツを用意
        FbxParts* pParts = new FbxParts;
        pParts->Init(_pNode);

        //パーツ情報を動的配列に追加
        _pPartsList->push_back(pParts);
    }


    //子ノードにもデータがあるかも！！
    {
        //子供の数を調べて
        int childCount = _pNode->GetChildCount();

        //一人ずつチェック
        for (int i = 0; i < childCount; i++)
        {
            CheckNode(_pNode->GetChild(i), _pPartsList);
        }
    }
}

Fbx::Fbx():_animSpeed(0)
{
}

Fbx::~Fbx()
{
    for (int i = 0; i < parts_.size(); i++)
    {
        delete parts_[i];
    }
    parts_.clear();

    pFbxScene_->Destroy();
    pFbxManager_->Destroy();
}

HRESULT Fbx::Load(string _fileName)
{
    //▼FBXの読み込み
    pFbxManager_ = FbxManager::Create();
    pFbxScene_ = FbxScene::Create(pFbxManager_, "fbxscene");
    FbxString FileName(_fileName.c_str());
    FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager_, "imp");
    if (!fbxImporter->Initialize(FileName.Buffer(), -1, pFbxManager_->GetIOSettings()))
    {
        //失敗
        return E_FAIL;
    }
    fbxImporter->Import(pFbxScene_);
    fbxImporter->Destroy();

    //▼アニメーションのタイムモードの取得
    _frameRate = pFbxScene_->GetGlobalSettings().GetTimeMode();


    //▼現在のカレントディレクトリを覚えておく
    char defaultCurrentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

    //▼カレントディレクトリをファイルがあった場所に変更
    char dir[MAX_PATH];
    _splitpath_s(_fileName.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
    SetCurrentDirectory(dir);

    //▼ルートノードを取得して
    FbxNode* rootNode = pFbxScene_->GetRootNode();

    //▼そいつの子供の数を調べて
    int childCount = rootNode->GetChildCount();

    //▼1個ずつチェック
    for (int i = 0; childCount > i; i++)
    {
        CheckNode(rootNode->GetChild(i), &parts_);
    }

    //▼カレントディレクトリを元の位置に戻す
    SetCurrentDirectory(defaultCurrentDir);

    return S_OK;
}

void Fbx::Draw(Transform& _transform,int _frame)
{
    Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

    for (int k = 0; k < parts_.size(); k++)
    {
        FbxTime time;
        time.SetTime(0, 0, 0, _frame, 0, 0, _frameRate);

        if (parts_[k]->GetSkinInfo() != nullptr)
        {
            parts_[k]->DrawSkinAnime(_transform, time);
        }
        else
        {
            parts_[k]->DrawMeshAnime(_transform, time, pFbxScene_);
        }
    }
}

void Fbx::Release()
{

}

XMFLOAT3 Fbx::GetBonePosition(string _boneName)
{
    XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < parts_.size(); i++)
    {
        if (parts_[i]->GetBonePosition(_boneName, &position))
        {
            break;
        }
    }

    return position;
}

void Fbx::RayCast(RayCastData* _data)
{
    //全てのパーツと判定
    for (int i = 0; i < parts_.size(); i++)
    {
        parts_[i]->RayCast(_data);
    }
}




