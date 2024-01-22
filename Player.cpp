#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1),camType_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets/PlayerC.fbx");
	assert(hModel_ >= 0);
}

void Player::Update()
{
    PlayerMove();

    //pCamera_->SetTarget(TransPlayer_.position_,0);
    //XMFLOAT3 camPos = TransPlayer_.position_;
    //camPos.y += 5;
    //camPos.z -= 10;
    //pCamera_->SetPosition(camPos,0);
}

void Player::Draw()
{
    Model::SetTransform(hModel_, TransPlayer_);
    Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::PlayerMove()
{
    if (Input::IsKey(DIK_SPACE))
    {
        TransPlayer_.position_.y += 0.2;
    }

    if (Input::IsKey(DIK_W))
    {
        TransPlayer_.position_.z += 0.2;
    }
    if (Input::IsKey(DIK_S))
    {
        TransPlayer_.position_.z -= 0.2;
    }

    if (Input::IsKey(DIK_D))
    {
        TransPlayer_.position_.x += 0.2;
    }
    if (Input::IsKey(DIK_A))
    {
        TransPlayer_.position_.x -= 0.2;
    }
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
    int hStageModel = pStage->GetModelHandle();   //モデル番号を取得

    RayCastData data;
    data.start = TransPlayer_.position_;  //レイの発射位置
    data.start.y = 0;
    data.dir = XMFLOAT3(0,-1, 0);       //レイの方向
    Model::RayCast(hStageModel,&data);  //レイを発射

    if (data.hit == true)
    {
        TransPlayer_.position_.y = -data.dist;
    }
}
