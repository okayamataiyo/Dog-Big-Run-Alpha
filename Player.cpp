#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_{ -1 ,-1}, camType_(0), playerNum_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//モデルデータのロード
	hModel_[0] = Model::Load("Assets/PlayerC.fbx");
	assert(hModel_[0] >= 0);

    hModel_[1] = Model::Load("Assets/Pipe.fbx");
    assert(hModel_[1] >= 0);

    playerNum_ = 0;

    TransPlayer_[1].position_.x = 5;
    powerY_[0] = 2;
}

void Player::Update()
{
    PlayerMove();

    for (int i = 0; i <= 1; i++)
    {

    }

    pCamera_->SetTarget(TransPlayer_[1].position_, 1);
    XMFLOAT3 camPos = TransPlayer_[1].position_;
    camPos.y += 5;
    camPos.z -= 10;
    pCamera_->SetPosition(camPos, 1);
}

void Player::Draw()
{
    for (int i = 0; i <= 1; i++)
    {
        Model::SetTransform(hModel_[i], TransPlayer_[i]);
        Model::Draw(hModel_[i]);
    }
}

void Player::Release()
{
}

void Player::PlayerMove()
{
    switch (playerNum_)
    {
    case PlayerFirst:
        TransPlayer_[0].position_ = { powerX_[playerNum_],powerY_[playerNum_],powerZ_[playerNum_] };
        break;
    case PlayerSeconds:
        TransPlayer_[1].position_ = { powerX_[playerNum_],powerY_[playerNum_],powerZ_[playerNum_] };
        break;
    }

    if (Input::IsKey(DIK_SPACE))
    {
        //powerY_ += 0.2;
        playerNum_ += 1;
        playerNum_ = playerNum_ % 2;
    }

    if (Input::IsKey(DIK_W))
    {
        powerZ_[playerNum_] += 0.2;
    }
    if (Input::IsKey(DIK_S))
    {
        powerZ_[playerNum_] -= 0.2;
    }

    if (Input::IsKey(DIK_D))
    {
        powerX_[playerNum_] += 0.2;
    }
    if (Input::IsKey(DIK_A))
    {
        powerX_[playerNum_] -= 0.2;
    }

    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
    int hStageModel = pStage->GetModelHandle();   //モデル番号を取得
    RayCastData data;

    for (int i = 0; i <= 1; i++)
    {
        data.start = TransPlayer_[i].position_;  //レイの発射位置
        data.start.y = 0;
        data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
        Model::RayCast(hStageModel, &data);  //レイを発射

        if (data.hit == true)
        {
            TransPlayer_[i].position_.y = -data.dist;
        }
    }

}
