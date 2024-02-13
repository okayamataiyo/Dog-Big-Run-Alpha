#include "Player.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "Stage.h"

Player::Player(GameObject* _pParent)
    :GameObject(_pParent, "Player"),TimeCounter_(0), hModel_{ -1 }, camType_(0), playerNum_(0), jumpFlg_(false), State_(READY)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Assets/Dog.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = { 0.5,0.5,0.5 };
    powerY_ = transform_.position_.y;
    for (int i = 0u; i <= 1; i++)
    {
        pCollision_ = new SphereCollider(XMFLOAT3(0.0, 0.0, 0.0), 1);
        AddCollider(pCollision_);
    }
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g
    hStageModel_ = pStage->GetModelHandle();   //���f���ԍ����擾

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
    PlayerMove();
    PlayerGravity();
    PlayerWall();
    if (Input::IsKey(DIK_SPACE) && jumpFlg_ == false)
    {
        PlayerJump();
    }
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
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    XMVECTOR vecPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vecMove = camera_.GetPosition(0);
    vecMove = XMVector3TransformCoord(vecMove, mRotY);

    if (jumpFlg_ == false)
    {
        velocity_.x *= 0.9f;    //X�������̊���
        velocity_.z *= 0.9f;    //Z�������̊���
    }
    else
    {
        velocity_.x *= 0.97f;
        velocity_.z *= 0.97f;
    }

    //transform_.position_.x += velocity_.x;
    //transform_.position_.z += velocity_.z;
    transform_.position_.y = powerY_;
    vecMove_ = XMLoadFloat3(&velocity_);
    vecMove_ = camera_.GetPosition(1);
    vecMove_ = XMVector3Normalize(vecMove_);
    vecMove_ *= 0.05f;
    //XMStoreFloat3(&velocity_[i], vecMove_[i]);

    //�����ύX
    vecLength_ = XMVector3Length(vecMove_);
    length_ = XMVectorGetX(vecLength_);

    if (length_ != 0)
    {
        //�v���C���[�����̓L�[�ɉ����āA���̌����ɕς���(�������ɂ͏o���Ȃ�)
        vecFront_ = {0,0,1,0};
        vecMove_ = XMVector3Normalize(vecMove_);

        vecDot_ = XMVector3Dot(vecFront_, vecMove_);
        dot_ = XMVectorGetX(vecDot_);
        angle_ = acos(dot_);

        //�E�����ɂ��������Ȃ��������̂��������ɂ��鎖���ł���
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

    if (Input::IsKey(DIK_W))
    {
        //velocity_.z += 0.005f;
        vecPos += vecMove;
        XMStoreFloat3(&transform_.position_, vecPos);
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_S))
    {
        //velocity_.z -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_D))
    {
        //velocity_.x += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_A))
    {
        //velocity_.x -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_C))
    {
        playerNum_ += 1;
        playerNum_ = playerNum_ % 2;
        GameSta_ = WALK;
    }

}

void Player::PlayerJump()
{
    //�W�����v�̏���
    jumpFlg_ = true;
    moveYPrev_ = powerY_;
    powerY_ = powerY_ + 0.2;
}

void Player::PlayerWall()
{
    
}

void Player::PlayerGravity()
{
    RayCastData downData;
    RayCastData frontData;

    if (jumpFlg_ == true)
    {
        moveYTemp_ = powerY_;
        powerY_ += (powerY_ - moveYPrev_) - 0.007;
        moveYPrev_ = moveYTemp_;
        if (powerY_ <= -rayGravityDist_)
        {
            jumpFlg_ = false;
        }
    }

    //�����̖@��(�d�͍Č�)
    downData.start = transform_.position_;  //���C�̔��ˈʒu
    downData.start.y = 0;
    downData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStageModel_, &downData);  //���C�𔭎�
    rayGravityDist_ = downData.dist;

    if (downData.hit == true)
    {
        if (jumpFlg_ == false)
        {
            transform_.position_.y = -downData.dist + 0.6;
            powerY_ = -downData.dist + 0.6;
        }
    }

    //���O�̖@��(�ǂ̓����蔻��)
    frontData.start = transform_.position_;  //���C�̔��ˈʒu
    frontData.start.z = 0;
    frontData.dir = XMFLOAT3(0, 0, 1);       //���C�̕���
    Model::RayCast(hStageModel_, &frontData);  //���C�𔭎�
    rayWallDist_ = frontData.dist;
}
