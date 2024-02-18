#include "Player.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "Stage.h"
#include "Engine/ImGui/imgui.h"

Player::Player(GameObject* _pParent)
    :GameObject(_pParent, "Player"),TimeCounter_(0), hModel_{ -1 }, camType_(0), playerNum_(0), jumpFlg_(false), State_(READY),isFloor_(0)
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
//    powerY_ = transform_.position_.y;
    for (int i = 0u; i <= 1; i++)
    {
        pCollision_ = new SphereCollider(XMFLOAT3(0.0, 0.0, 0.0), 1);
        AddCollider(pCollision_);
        Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
        hStageModel_[i] = pStage->GetModelHandle(i);   //モデル番号を取得
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
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::UpdateReady()
{
    //PlayerGravity();
    ++TimeCounter_;
    if (TimeCounter_ >= 60)
    {
        State_ = STATE::PLAY;
        TimeCounter_ = 0;
    }
}

void Player::UpdatePlay()
{
    PlayerGravity();
    PlayerMove();
    ImGui::Text("moveYPrev_%f", moveYPrev_);
    ImGui::Text("moveYTemp_%f", moveYTemp_);
//    ImGui::Text("powerY_%f", powerY_);
    ImGui::Text("jumpFlg_%s", jumpFlg_ ? "true":"false");
    
    PlayerWall();
}

void Player::UpdateGameOver()
{
    ++TimeCounter_;
    if (Input::IsKey(DIK_SPACE))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }
}

void Player::OnCollision(GameObject* _pTarget)
{
    if (_pTarget->GetObjectName() == "Item")
    {
        PlayerJump();
    }

    if (_pTarget->GetObjectName() == "PlayerSeconds")
    {
        if (State_ != STATE::GAMEOVER)
        {
            Direct3D::SetIsChangeView(1);
            State_ = STATE::GAMEOVER;
        }
    }
}

void Player::PlayerMove()
{
    if (jumpFlg_ == false)
    {
//        velocity_.x *= 0.9f;    //X軸方向の慣性
//        velocity_.z *= 0.9f;    //Z軸方向の慣性
    }
    else
    {
//        velocity_.x *= 0.97f;
//        velocity_.z *= 0.97f;
    }


    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    XMVECTOR vecPos = XMLoadFloat3(&transform_.position_);
    //XMVECTOR vecMove = camera_.GetPosition(0);
    //vecMove = XMVector3TransformCoord(vecMove, mRotY);

    //transform_.position_.x += velocity_.x;
    //transform_.position_.z += velocity_.z;
//    transform_.position_.y = powerY_;
    XMVECTOR vecCam = -(camera_.GetPosition(0) - camera_.GetTarget(0));
    vecCam = XMVector3Normalize(vecCam);
    //vecMove_ = XMLoadFloat3(&velocity_);
    //vecMove_ = XMVector3Normalize(vecMove_);
    vecMove_ = vecCam;
    vecMove_ *= 0.005f;

    //向き変更
    vecLength_ = XMVector3Length(vecMove_);
    //length_ = XMVectorGetX(vecLength_);

    //if (length_ != 0)
    //{
    //    //プレイヤーが入力キーに応じて、その向きに変える(左向きには出来ない)
    //    vecFront_ = { 0,0,1,0 };
    //    vecMove_ = XMVector3Normalize(vecMove_);

    //    vecDot_ = XMVector3Dot(vecFront_, vecMove_);
    //    dot_ = XMVectorGetX(vecDot_);
    //    angle_ = acos(dot_);

    //    //右向きにしか向けなかったものを左向きにする事ができる
    //    vecCross_ = XMVector3Cross(vecFront_, vecMove_);
    //    if (XMVectorGetY(vecCross_) < 0)
    //    {
    //        angle_ *= -1;
    //    }

    //    transform_.rotate_.y = XMConvertToDegrees(angle_);
    //}

    if (Input::IsKey(DIK_LSHIFT))
    {
        if (jumpFlg_ == false)
        {
//            velocity_.x = velocity_.x * 1.1;
//            velocity_.z = velocity_.z * 1.1;
            GameSta_ = RUN;
        }
    }

    if (this->GetObjectName() == "PlayerSeconds")
    {
        if (Input::IsKey(DIK_W))
        {
            XMVECTOR vectorMove = vecMove_ + XMLoadFloat3(&transform_.position_);
            
            XMStoreFloat3(&transform_.position_, vectorMove);
        }
        if (Input::IsKey(DIK_S))
        {
            XMVECTOR vectorMove = XMLoadFloat3(&transform_.position_) - vecMove_;

            XMStoreFloat3(&transform_.position_, vectorMove);
        }

        if (Input::IsKey(DIK_D))
        {
            //XMMatrixRotationY = Y座標を中心に回転させる行列を作る関数
            //XMConvertToRadians = degree角をradian角に(ただ)変換する
            XMMATRIX mRotationY = XMMatrixRotationY(XMConvertToRadians(90));
            XMVECTOR vectorMove = XMLoadFloat3(&transform_.position_) + vecMove_;
            vectorMove = XMVector3Transform(vectorMove, mRotationY);
            XMStoreFloat3(&transform_.position_,vectorMove);
        }
        if (Input::IsKey(DIK_A))
        {
//            velocity_.x -= 0.005f;
        }
        if (Input::IsKey(DIK_SPACE) && jumpFlg_ == false)
        {
             PlayerJump();
        }
    }
    if (this->GetObjectName() == "PlayerFirst")
    {
        transform_.position_.x += Input::GetPadStickL().x / 2;
        transform_.position_.z += Input::GetPadStickL().y / 2;
        if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && jumpFlg_ == false)
        {
            PlayerJump();
        }
    }
}

void Player::PlayerJump()
{
    //ジャンプの処理
    jumpFlg_ = true;
    moveYPrev_ = transform_.position_.y;
    transform_.position_.y = transform_.position_.y + 0.3;
}

void Player::PlayerWall()
{
    
}

void Player::PlayerGravity()
{
    RayCastData upData;
    RayCastData floorData;
    RayCastData downData;
    RayCastData frontData;
    if (jumpFlg_ == true)
    {
        //放物線に下がる処理
        moveYTemp_ = transform_.position_.y;
        transform_.position_.y += (transform_.position_.y - moveYPrev_) - 0.007;
        moveYPrev_ = moveYTemp_;
        if (transform_.position_.y <= -rayDownDist_ + 0.6)
        {
            jumpFlg_ = false;
        }
        if (transform_.position_.y <= -rayGravityDist_ + 0.6)
        {
            jumpFlg_ = false;
        }
    }

    //▼上の法線(すり抜け床のため)
    upData.start = transform_.position_;       //レイの発射位置
    upData.dir = XMFLOAT3(0, 1, 0);            //レイの方向
    Model::RayCast(hStageModel_[1], &upData);  //レイを発射
    rayUpDist_ = upData.dist;

    //▼下の法線(すり抜け床)
    floorData.start = transform_.position_;    //レイの発射位置
    floorData.start.y = 0;
    floorData.dir = XMFLOAT3(0, -1, 0);        //レイの方向
    if (upData.dist == 99999)
    {
        Model::RayCast(hStageModel_[1], &floorData);  //レイを発射
    }
    rayDownDist_ = floorData.dist;

    if (floorData.hit == true)
    {
        if (jumpFlg_ == false)
        {
            transform_.position_.y = -floorData.dist + 0.6;
            isFloor_ = 1;
        }
    }
    else
    {
        isFloor_ = 0;
    }

    //▼下の法線(床に張り付き)
    downData.start = transform_.position_;  //レイの発射位置
    downData.start.y = 0;
    downData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStageModel_[0], &downData);  //レイを発射
    rayGravityDist_ = downData.dist;
    float playerFling = 0.7;
    //プレイヤーが浮いていないとき
    ImGui::Text("dist=%f",downData.dist);
    if (downData.dist + transform_.position_.y <= playerFling)
    {
        //ジャンプしてない＆すり抜け床の上にいない
        if (jumpFlg_ == false && isFloor_ == 0)
        {
            //地面に張り付き
            transform_.position_.y = -downData.dist + 0.6;
        }
    }
    else if(isFloor_ == 0)
    {
        jumpFlg_ = true;
    }
    //▼前の法線(壁の当たり判定)
    frontData.start = transform_.position_;       //レイの発射位置
    frontData.dir = XMFLOAT3(0, 0, 1);            //レイの方向
    Model::RayCast(hStageModel_[0], &frontData);  //レイを発射
    rayWallDist_ = frontData.dist;
    prevIsFloor_ = isFloor_;
}