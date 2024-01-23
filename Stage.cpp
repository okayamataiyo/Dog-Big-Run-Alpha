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

    Trans_G.position_.y = -10;
    Trans_G.rotate_.y = 90;
    Trans_G.scale_ = { 1,0.5,1 };
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