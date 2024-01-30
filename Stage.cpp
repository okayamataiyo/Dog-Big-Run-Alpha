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
    //�ŏ���3D�ŕ`���A�g�Â����`��
    Model::SetTransform(hModel_, Trans_G);
    for (int i = 3; i >= 1; i -= 2)
    {
        Direct3D::SetShader(static_cast<SHADER_TYPE>(i));
        Model::Draw(hModel_);
    }
}

//�J��
void Stage::Release()
{
}