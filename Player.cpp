#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"

Player::Player(GameObject* _parent)
    :GameObject(_parent, "Player"),TimeCounter_(0), hModel_{ -1 }, camType_(0), playerNum_(0), jumpFlg_{ false,false }, State_(READY)
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
    for (int i = 0u; i <= 1; i++)
    {
        powerY_[i] = transPlayer_[i].position_.y;
    }

    pCollision = new BoxCollider(XMFLOAT3(0.0,0.0,0.0), XMFLOAT3(1.1,1.1,1.1));
    AddCollider(pCollision);

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
        Model::SetTransform(hModel_, transPlayer_[i]);
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
        transform_ = transPlayer_[i];
        PlayerJump(i);
        pCamera->SetTarget(transPlayer_[i].position_, i);
        XMFLOAT3 camPos = transPlayer_[i].position_;
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
        if (jumpFlg_[i] == false)
        {
            velocity_[i].x *= 0.9f;    //X�������̊���
            velocity_[i].z *= 0.9f;    //Z�������̊���
        }
        else
        {
            velocity_[i].x *= 0.97f;
            velocity_[i].z *= 0.97f;
        }
        transPlayer_[i].position_.x += velocity_[i].x;
        transPlayer_[i].position_.z += velocity_[i].z;
        transPlayer_[i].position_.y = powerY_[i];
        vecMove_[i] = XMLoadFloat3(&velocity_[i]);
        vecMove_[i] = XMVector3Normalize(vecMove_[i]);
        vecMove_[i] *= 0.05f;
        //XMStoreFloat3(&velocity_[i], vecMove_[i]);

        //�����ύX
        vecLength_[i] = XMVector3Length(vecMove_[i]);
        length_[i] = XMVectorGetX(vecLength_[i]);

        if (length_[i] != 0)
        {
            //�v���C���[�����̓L�[�ɉ����āA���̌����ɕς���(�������ɂ͏o���Ȃ�)
            vecFront_[i] = {0,0,1,0};
            vecMove_[i] = XMVector3Normalize(vecMove_[i]);

            vecDot_[i] = XMVector3Dot(vecFront_[i], vecMove_[i]);
            dot_[i] = XMVectorGetX(vecDot_[i]);
            angle_[i] = acos(dot_[i]);

            //�E�����ɂ��������Ȃ��������̂��������ɂ��鎖���ł���
            vecCross_[i] = XMVector3Cross(vecFront_[i], vecMove_[i]);
            if (XMVectorGetY(vecCross_[i]) < 0)
            {
                angle_[i] *= -1;
            }

            transPlayer_[i].rotate_.y = XMConvertToDegrees(angle_[i]);
        }

        if (Input::IsKey(DIK_LSHIFT))
        {
            if (jumpFlg_[i] == false)
            {
                velocity_[i].x = velocity_[i].x * 1.1;
                velocity_[i].z = velocity_[i].z * 1.1;
                GameSta_ = RUN;
            }
        }
    }
    //���v���C���[�E�̐l
    if (Input::IsKey(DIK_UP))
    {
        velocity_[1].z += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        velocity_[1].z -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        velocity_[1].x += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_LEFT))
    {
        velocity_[1].x -= 0.005f;
        GameSta_ = WALK;
    }
    //���v���C���[���̐l
    if (Input::IsKey(DIK_W))
    {
        velocity_[0].z += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_S))
    {
        velocity_[0].z -= 0.005f;
        GameSta_ = WALK;
    }

    if (Input::IsKey(DIK_D))
    {
        velocity_[0].x += 0.005f;
        GameSta_ = WALK;
    }
    if (Input::IsKey(DIK_A))
    {
        velocity_[0].x -= 0.005f;
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
    RayCastData data[2];
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g
    int hStageModel = pStage->GetModelHandle();   //���f���ԍ����擾


    for (int i = 0u; i <= 1; i++)
    {
        //�W�����v�̏���
        if (jumpFlg_[i] == true)
        {
            moveYTemp_[i] = powerY_[i];
            powerY_[i] += (powerY_[i] - moveYPrev_[i]) - 0.003;
            moveYPrev_[i] = moveYTemp_[i];
            if (powerY_[i] <= -rayDist_[i])
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
        
        //���C�̏���
        data[i].start = transPlayer_[i].position_;  //���C�̔��ˈʒu
        data[i].start.y = 0;
        data[i].dir = XMFLOAT3(0, -1, 0);       //���C�̕���
        Model::RayCast(hStageModel, &data[i]);  //���C�𔭎�
        rayDist_[i] = data[i].dist;

        if (data[i].hit == true)
        {
            if (jumpFlg_[i] == false)
            {
                transPlayer_[i].position_.y = -data[i].dist + 0.6;
                powerY_[i] = -data[i].dist + 0.6;
            }


        }
    }
}
