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

//更新
void Stage::Update()
{

}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, Trans_G);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}