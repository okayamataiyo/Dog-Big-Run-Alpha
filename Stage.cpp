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
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);

    Trans_G.position_.y = -10;
    Trans_G.rotate_.y = 90;
    Trans_G.scale_ = { 1,0.5,1 };
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