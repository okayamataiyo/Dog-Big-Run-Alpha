#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Stage.h"

Transform Trans_P;

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
    Camera* pCamera = new Camera;
    PlayerMove();

    pCamera->SetTarget(Trans_P.position_,0);
    XMFLOAT3 camPos = Trans_P.position_;
    camPos.y += 5;
    camPos.z -= 10;
    pCamera->SetPosition(camPos,0);
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
}
