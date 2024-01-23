#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"

Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_{ -1 ,-1 }, camType_(0), playerNum_(0), jumpFlg_{ false,false }
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//モデルデータのロード
    for (int i = 0; i <= 1; i++)
    {
        hModel_[i] = Model::Load("Assets/PlayerC.fbx");
        assert(hModel_[i] >= 0);
    }

}

void Player::Update()
{
    PlayerMove();

    for (int i = 0; i <= 1; i++)
    {
        pCamera->SetTarget(TransPlayer_[i].position_, i);
        XMFLOAT3 camPos = TransPlayer_[i].position_;
        camPos.y += 5;
        camPos.z -= 10;
        pCamera->SetPosition(camPos, i);
    }
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
    if (Input::IsKey(DIK_UP))
    {
        powerZ_[1] += 0.2;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        powerZ_[1] -= 0.2;
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        powerX_[1] += 0.2;
    }
    if (Input::IsKey(DIK_LEFT))
    {
        powerX_[1] -= 0.2;
    }

    if (Input::IsKey(DIK_W))
    {
        powerZ_[0] += 0.2;
    }
    if (Input::IsKey(DIK_S))
    {
        powerZ_[0] -= 0.2;
    }

    if (Input::IsKey(DIK_D))
    {
        powerX_[0] += 0.2;
    }
    if (Input::IsKey(DIK_A))
    {
        powerX_[0] -= 0.2;
    }

    if (Input::IsKey(DIK_C))
    {
        playerNum_ += 1;
        playerNum_ = playerNum_ % 2;
    }

    RayCastData data[2];
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
    int hStageModel = pStage->GetModelHandle();   //モデル番号を取得

    for (int i = 0; i <= 1; i++)
    {
        TransPlayer_[i].position_ = { powerX_[i],powerY_[i],powerZ_[i] };

        if (jumpFlg_[i] == true)
        {
            moveYTemp_[i] = powerY_[i];
            powerY_[i] += (powerY_[i] - moveYPrev_[i]) - 0.005;
            moveYPrev_[i] = moveYTemp_[i];
            if (powerY_[i] <= 10)
            {
                jumpFlg_[i] = false;
            }
        }

        if (Input::IsKey(DIK_SPACE) && jumpFlg_[0] == false)
        {
            jumpFlg_[0] = true;
            moveYPrev_[0] = powerY_[0];
            powerY_[0] = powerY_[0] + 0.2;
        }

        if (Input::IsKey(DIK_RSHIFT) && jumpFlg_[1] == false)
        {
            jumpFlg_[1] = true;
            moveYPrev_[1] = powerY_[1];
            powerY_[1] = powerY_[1] + 0.2;
        }

        data[i].start = TransPlayer_[i].position_;  //レイの発射位置
        data[i].start.y = 0;
        data[i].dir = XMFLOAT3(0, -1, 0);       //レイの方向
        Model::RayCast(hStageModel, &data[i]);  //レイを発射
        aaa = data[i].dist;

        if (data[i].hit == true)
        {
            if (jumpFlg_[0] == false)
            {
                TransPlayer_[0].position_.y = -data[0].dist;
            }

            if (jumpFlg_[1] == false)
            {
                TransPlayer_[1].position_.y = -data[1].dist;
            }
        }
    }
}
