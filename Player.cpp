#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Stage.h"

Camera* pCamera_ = new Camera;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1),camType_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets/PlayerC.fbx");
	assert(hModel_ >= 0);
}

void Player::Update()
{
    PlayerMove();

    pCamera_->SetTarget(Trans_P.position_,0);
    XMFLOAT3 camPos = Trans_P.position_;
    camPos.y += 5;
    camPos.z -= 10;
    pCamera_->SetPosition(camPos,0);
}

void Player::Draw()
{
    Model::SetTransform(hModel_, Trans_P);
    Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::PlayerMove()
{
    if (Input::IsKey(DIK_SPACE))
    {
        Trans_P.position_.y += 0.2;
    }

    if (Input::IsKey(DIK_W))
    {
        Trans_P.position_.z += 0.2;
    }
    if (Input::IsKey(DIK_S))
    {
        Trans_P.position_.z -= 0.2;
    }

    if (Input::IsKey(DIK_D))
    {
        Trans_P.position_.x += 0.2;
    }
    if (Input::IsKey(DIK_A))
    {
        Trans_P.position_.x -= 0.2;
    }
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g
    int hStageModel = pStage->GetModelHandle();   //���f���ԍ����擾

    RayCastData data;
    data.start = Trans_P.position_;  //���C�̔��ˈʒu
    data.start.y = 0;
    data.dir = XMFLOAT3(0,-1, 0);       //���C�̕���
    Model::RayCast(hStageModel,&data);  //���C�𔭎�

    if (data.hit == true)
    {
        Trans_P.position_.y = -data.dist;
    }
}
