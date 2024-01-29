//�C���N���[�h
#include "Engine/Model.h"
#include "Item.h"
#include "Stage.h"

Item::Item(GameObject* _parent)
	:GameObject(_parent, "Item"), hModel_(-1)
{

}

Item::~Item()
{
}

void Item::Initialize()
{
	hModel_ = Model::Load("Assets/Bone.fbx");
	assert(hModel_ >= 0);

	BoxCollider* pCollision = new BoxCollider(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT3(1.1, 0.5, 1.1));
	AddCollider(pCollision);

	transform_.scale_ = { 0.2,0.2,0.2 };
}

void Item::Update()
{
	RayCastData data;
	Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g
	int hStageModel = pStage->GetModelHandle();   //���f���ԍ����擾

	data.start = transform_.position_;  //���C�̔��ˈʒu
	data.start.y = 0;
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStageModel, &data);  //���C�𔭎�
	rayDist_ = data.dist;

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist + 0.6;
	}
}

void Item::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	GameObject::CollisionDraw();
}

void Item::Release()
{
}

void Item::OnCollision(GameObject* _pTarget)
{
	if (_pTarget->GetObjectName() == "PlayerFirst")
	{
		transform_.position_.x += 1;
	}
}
