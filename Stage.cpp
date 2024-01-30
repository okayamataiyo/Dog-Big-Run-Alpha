#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Stage.h"

Stage::Stage(GameObject* _parent)
    :GameObject(_parent, "Stage"),hModel_(-1)
{

}

Stage::~Stage()
{

}

void Stage::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = -5;
    transform_.rotate_.y = 90;
    transform_.scale_ = { 4,1,4 };
}

void Stage::Update()
{

}

void Stage::Draw()
{
    //最初に3Dで描画後、枠づけも描画
    Model::SetTransform(hModel_, transform_);
    for (int i = 3; i >= 1; i -= 2)
    {
        Direct3D::SetShader(static_cast<SHADER_TYPE>(i));
        Model::Draw(hModel_);
    }
}

void Stage::Release()
{
}