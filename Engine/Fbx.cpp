#include <assert.h>
#include "Fbx.h"
#include "Direct3D.h"
#include "FbxParts.h"

void Fbx::CheckNode(FbxNode* _pNode, vector<FbxParts*>* _pPartsList)
{
    //���̃m�[�h�ɂ̓��b�V����񂪓����Ă��邾�낤���H
    FbxNodeAttribute* attr = _pNode->GetNodeAttribute();
    if (attr != nullptr && attr->GetAttributeType() == FbxNodeAttribute::eMesh)
    {
        //�p�[�c��p��
        FbxParts* pParts = new FbxParts;
        pParts->Init(_pNode);

        //�p�[�c���𓮓I�z��ɒǉ�
        _pPartsList->push_back(pParts);
    }


    //�q�m�[�h�ɂ��f�[�^�����邩���I�I
    {
        //�q���̐��𒲂ׂ�
        int childCount = _pNode->GetChildCount();

        //��l���`�F�b�N
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
    //��FBX�̓ǂݍ���
    pFbxManager_ = FbxManager::Create();
    pFbxScene_ = FbxScene::Create(pFbxManager_, "fbxscene");
    FbxString FileName(_fileName.c_str());
    FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager_, "imp");
    if (!fbxImporter->Initialize(FileName.Buffer(), -1, pFbxManager_->GetIOSettings()))
    {
        //���s
        return E_FAIL;
    }
    fbxImporter->Import(pFbxScene_);
    fbxImporter->Destroy();

    //���A�j���[�V�����̃^�C�����[�h�̎擾
    _frameRate = pFbxScene_->GetGlobalSettings().GetTimeMode();


    //�����݂̃J�����g�f�B���N�g�����o���Ă���
    char defaultCurrentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

    //���J�����g�f�B���N�g�����t�@�C�����������ꏊ�ɕύX
    char dir[MAX_PATH];
    _splitpath_s(_fileName.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
    SetCurrentDirectory(dir);

    //�����[�g�m�[�h���擾����
    FbxNode* rootNode = pFbxScene_->GetRootNode();

    //�������̎q���̐��𒲂ׂ�
    int childCount = rootNode->GetChildCount();

    //��1���`�F�b�N
    for (int i = 0; childCount > i; i++)
    {
        CheckNode(rootNode->GetChild(i), &parts_);
    }

    //���J�����g�f�B���N�g�������̈ʒu�ɖ߂�
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
    //�S�Ẵp�[�c�Ɣ���
    for (int i = 0; i < parts_.size(); i++)
    {
        parts_[i]->RayCast(_data);
    }
}




