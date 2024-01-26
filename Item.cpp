//インクルード
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
	hModel_ = Model::Load("Assets/PlayerC.fbx");
	assert(hModel_ >= 0);

	BoxCollider* pCollision = new BoxCollider(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT3(1.1, 1.1, 1.1));
	AddCollider(pCollision);
}

void Item::Update()
{
	RayCastData data;
	Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクト
	int hStageModel = pStage->GetModelHandle();   //モデル番号を取得

	data.start = transform_.position_;  //レイの発射位置
	data.start.y = 0;
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStageModel, &data);  //レイを発射
	rayDist_ = data.dist;

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
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
}
