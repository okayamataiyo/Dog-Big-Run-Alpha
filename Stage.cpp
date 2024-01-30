#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Stage.h"

Transform Trans_G;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_(-1)
{

}

//�f�X�g���N�^
Stage::~Stage()
{

}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    for (int i = 0u; i <= 1; i++)
    {
        //ModelName_[i] += "Assets/";
        //ModelName_[i] += "ss";
        hModel_ = Model::Load(ModelName_[i]);
        assert(hModel_ >= i);
    }
    Trans_G.position_.y = -5;
    Trans_G.rotate_.y = 90;
    Trans_G.scale_ = { 4,1,4 };
}

//�X�V
void Stage::Update()
{

}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, Trans_G);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}