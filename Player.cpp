#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"

Player::Player(GameObject* _parent)
    :GameObject(_parent, "Player"),TimeCounter_(0), hModel_{ -1 }, camType_(0), playerNum_(0), jumpFlg_(false), State_(READY)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/Dog.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = { 0.5,0.5,0.5 };
    for (int i = 0u; i <= 1; i++)
    {
        powerY_ = transform_.position_.y;

        pCollision_ = new BoxCollider(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT3(1.1, 1.1, 1.1));
        AddCollider(pCollision_);
    }

}

void Player::Update()
{
    switch(State_)
    {
    case STATE::READY:     UpdateReady();    break;
    case STATE::PLAY:      UpdatePlay();     break;
    case STATE::GAMEOVER:  UpdateGameOver(); break;
    }
}

void Player::Draw()
{
    for (int i = 0u; i <= 1; i++)
    {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
    GameObject::CollisionDraw();
}

void Player::Release()
{
}

void Player::UpdateReady()
{
    ++TimeCounter_;
    if (TimeCounter_ >= 60)
    {
        State_ = STATE::PLAY;
        TimeCounter_ = 0;
    }
}

void Player::UpdatePlay()
{
    PlayerMove();
    for (int i = 0u; i <= 1; i++)
    {
        //transform_ = transPlayer_[i];
        PlayerJump(i);
        pCamera->SetTarget(transform_.position_, i);
        XMFLOAT3 camPos = transform_.position_;
        camPos.y += 2;
        camPos.z -= 15;
        pCamera->SetPosition(camPos, i);
    }
}

void Player::UpdateGameOver()
{
    ++TimeCounter_;
    if (TimeCounter_ >= 60)
    {

    }
}

void Player::OnCollision(GameObject* _pTarget)
{
    if (_pTarget->GetObjectName() == "Item")
    {
        PlayerJump(1);
    }
}

void Player::PlayerMove()
{
    for (int i = 0u; i <= 1; i++)
    {
        if (jumpFlg_ == false)
        {
            velocity_.x *= 0.9f;    //X軸方向の慣性
            velocity_.z *= 0.9f;    //Z軸方向の慣性
        }
        else
        {
            velocity_.x *= 0.97f;
            velocity_.z *= 0.97f;
        }
        transform_.position_.x += velocity_.x;
        transform_.position_.z += velocity_.z;
        transform_.position_.y = powerY_;
        vecMove_ = XMLoadFloat3(&velocity_);
        vecMove_ = XMVector3Normalize(vecMove_);
        vecMove_ *= 0.05f;
        //XMStoreFloat3(&velocity_[i], vecMove_[i]);

        //向き変更
        vecLength_ = XMVector3Length(vecMove_);
        length_ = XMVectorGetX(vecLength_);

        if (length_ != 0)
        {
            //プレイヤーが入力キーに応じて、その向きに変える(左向きには出来ない)
            vecFront_ = {0,0,1,0};
            vecMove_ = XMVector3Normalize(vecMove_);

            vecDot_ = XMVector3Dot(vecFront_, vecMove_);
            dot_ = XMVectorGetX(vecDot_);
            angle_ = acos(dot_);

            //右向きにしか向けなかったものを左向きにする事ができる
            vecCross_ = XMVector3Cross(vecFront_, vecMove_);
            if (XMVectorGetY(vecCross_) < 0)
            {
                angle_ *= -1;
            }

            transform_.rotate_.y = XMConvertToDegrees(angle_);
        }

        if (Input::IsKey(DIK_LSHIFT))
        {
            if (jumpFlg_ == false)
            {
                velocity_.x = velocity_.x * 1.1;
                velocity_.z = velocity_.z * 1.1;
                GameSta_ = RUN;
            }
        }
    }
    //▼プレイヤー右の人
    if (Input::IsKey(DIK_UP))
    {
        velocity_.z += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        velocity_.z -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        velocity_.x += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_LEFT))
    {
        velocity_.x -= 0.005f;
        GameSta_ = WALK;
    }
    //▼プレイヤー左の人
    if (Input::IsKey(DIK_W))
    {
        velocity_.z += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_S))
    {
        velocity_.z -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_D))
    {
        velocity_.x += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_A))
    {
        velocity_.x -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_C))
    {
        playerNum_ += 1;
        playerNum_ = playerNum_ % 2;
        GameSta_ = WALK;
    }

}

void Player::PlayerJump(int _PlayerNum)
{
    RayCastData data;
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
    int hStageModel = pStage->GetModelHandle();   //モデル番号を取得


    for (int i = 0u; i <= 1; i++)
    {
        //ジャンプの処理
        if (jumpFlg_ == true)
        {
            moveYTemp_ = powerY_;
            powerY_ += (powerY_ - moveYPrev_) - 0.004;
            moveYPrev_ = moveYTemp_;
            if (powerY_ <= -rayDist_)
            {
                jumpFlg_ = false;
            }
        }

        if (Input::IsKey(DIK_SPACE) && jumpFlg_ == false)
        {
            jumpFlg_ = true;
            moveYPrev_ = powerY_;
            powerY_ = powerY_ + 0.2;
        }

        if (Input::IsKey(DIK_RSHIFT) && jumpFlg_ == false)
        {
            jumpFlg_ = true;
            moveYPrev_ = powerY_;
            powerY_ = powerY_ + 0.2;
        }
        
        //レイの処理
        data.start = transform_.position_;  //レイの発射位置
        data.start.y = 0;
        data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
        Model::RayCast(hStageModel, &data);  //レイを発射
        rayDist_ = data.dist;

        if (data.hit == true)
        {
            if (jumpFlg_ == false)
            {
                transform_.position_.y = -data.dist + 0.6;
                powerY_ = -data.dist + 0.6;
            }


        }
    }
}
