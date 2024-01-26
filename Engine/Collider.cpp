#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"

//コンストラクタ
Collider::Collider() :
	pGameObject_(nullptr)
{
}

//デストラクタ
Collider::~Collider()
{
}

//箱型同士の衝突判定
//引数：boxA	１つ目の箱型判定
//引数：boxB	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsBox(BoxCollider* _boxA, BoxCollider* _boxB)
{

	XMFLOAT3 boxPosA = Transform::Float3Add(_boxA->pGameObject_->GetWorldPosition(), _boxA->center_);
	XMFLOAT3 boxPosB = Transform::Float3Add(_boxB->pGameObject_->GetWorldPosition(), _boxB->center_);


	if ((boxPosA.x + _boxA->size_.x / 2) > (boxPosB.x - _boxB->size_.x / 2) &&
		(boxPosA.x - _boxA->size_.x / 2) < (boxPosB.x + _boxB->size_.x / 2) &&
		(boxPosA.y + _boxA->size_.y / 2) > (boxPosB.y - _boxB->size_.y / 2) &&
		(boxPosA.y - _boxA->size_.y / 2) < (boxPosB.y + _boxB->size_.y / 2) &&
		(boxPosA.z + _boxA->size_.z / 2) > (boxPosB.z - _boxB->size_.z / 2) &&
		(boxPosA.z - _boxA->size_.z / 2) < (boxPosB.z + _boxB->size_.z / 2))
	{
		return true;
	}
	return false;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* _box, SphereCollider* _sphere)
{
	XMFLOAT3 circlePos = Transform::Float3Add(_sphere->pGameObject_->GetWorldPosition(), _sphere->center_);
	XMFLOAT3 boxPos = Transform::Float3Add(_box->pGameObject_->GetWorldPosition(), _box->center_);



	if (circlePos.x > boxPos.x - _box->size_.x - _sphere->size_.x &&
		circlePos.x < boxPos.x + _box->size_.x + _sphere->size_.x &&
		circlePos.y > boxPos.y - _box->size_.y - _sphere->size_.x &&
		circlePos.y < boxPos.y + _box->size_.y + _sphere->size_.x &&
		circlePos.z > boxPos.z - _box->size_.z - _sphere->size_.x &&
		circlePos.z < boxPos.z + _box->size_.z + _sphere->size_.x)
	{
		return true;
	}

	return false;
}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* _circleA, SphereCollider* _circleB)
{
	XMFLOAT3 centerA = _circleA->center_;
	XMFLOAT3 positionA = _circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = _circleB->center_;
	XMFLOAT3 positionB = _circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= _circleA->size_.x + _circleB->size_.x)
	{
		return true;
	}

	return false;
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 _position)
{
	Transform transform;
	transform.position_ = XMFLOAT3(_position.x + center_.x, _position.y + center_.y, _position.z + center_.z);
	transform.scale_ = size_;
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
