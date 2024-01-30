#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Stage.h"

Transform Trans_G;

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_(-1)
{

}

//デストラクタ
Stage::~Stage()
{

}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);

    Trans_G.position_.y = -5;
    Trans_G.rotate_.y = 90;
    Trans_G.scale_ = { 4,1,4 };
}

//更新
void Stage::Update()
{

}

//描画
void Stage::Draw()
{
    //最初に3Dで描画後、枠づけも描画
    Model::SetTransform(hModel_, Trans_G);
    for (int i = 3; i >= 1; i -= 2)
    {
        Direct3D::SetShader(static_cast<SHADER_TYPE>(i));
        Model::Draw(hModel_);
    }
}

//開放
void Stage::Release()
{
}