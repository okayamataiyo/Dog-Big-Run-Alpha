#include "GameObject.h"
#include "SphereCollider.h"
#include "Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* _parent, const std::string& _name)
	: pParent_(_parent), Is_DeadFlag(false), objectName_(_name), pCollider_(nullptr)
{
	if (pParent_ != nullptr) {
		this->transform_.pParent_ = &(_parent->transform_);
	}

}
//template <class T>

void Instantiate(GameObject* _parent)
{
	/*T* pPlayScene;
	pPlayScene = new T(parent);
	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
}

GameObject::~GameObject()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

bool GameObject::IsDead()
{
	return(Is_DeadFlag != false );
}

void GameObject::KillMe()
{
	Is_DeadFlag = true;
}

void GameObject::SetPosition(XMFLOAT3 _position)
{
	transform_.position_ = _position;
}

void GameObject::SetPosition(float _x, float _y, float _z)
{
	SetPosition(XMFLOAT3(_x, _y, _z));
}

GameObject* GameObject::GetParent()
{
	return pParent_;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {

		return(this);	//自分が_objNameのオブジェクトだった！
	}
	else {

//		for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		for(auto itr: childList_){

			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// 再帰呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス(GameObject * 型)</returns>
GameObject* GameObject::GetRootJob()
{

	if(pParent_ == nullptr)	return this;
	
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName) 
{

	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(_objName);
	return (result);
//	return GetRootJob()->FindObject(_objName);
}

void GameObject::DrawSub()
{
	Draw();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();) {

		if ((*itr)->IsDead() == true) {

			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);				//自分自身を消す
			itr = childList_.erase(itr);	//リストからも削除
		}
		else {
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {

		(*itr)->ReleaseSub();	//*itrのリリースを呼ぶ
		SAFE_DELETE(*itr);		//*itr自体を消す
	}

	Release();
}

void GameObject::AddCollider(Collider* _pCollider)
{

	_pCollider->SetGameObject(this);
	colliderList_.push_back(_pCollider);

}

void GameObject::Collision(GameObject* _pTarget)
{

	if (_pTarget == this || _pTarget->pCollider_ == nullptr) 
		return;		//ターゲットにコライダーがアタッチされていない

		//XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
		//			transform_.position_.y - pTarget->transform_.position_.y,
		//			transform_.position_.z - pTarget->transform_.position_.z,
		//			0 };
		//XMVECTOR dist = XMVector3Dot(v, v);
		/*float dist = (transform_.position_.x - _pTarget->transform_.position_.x) * (transform_.position_.x - _pTarget->transform_.position_.x)
			+ (transform_.position_.y - _pTarget->transform_.position_.y) * (transform_.position_.y - _pTarget->transform_.position_.y)
			+ (transform_.position_.z - _pTarget->transform_.position_.z) * (transform_.position_.z - _pTarget->transform_.position_.z);

		float rDist = (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius());*/

	//自分とターゲットの距離	<= R1+R2なら
	//もし、自分のコライダーとターゲットがぶつかっていたら
	//onCollision(pTarget)を呼び出す
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		for (auto j = _pTarget->colliderList_.begin(); j != _pTarget->colliderList_.end(); j++)
		{
			if ((*i)->IsHit(*j))
			{
				this->OnCollision(_pTarget);
			}
		}
	}

	if (_pTarget->childList_.empty())
	{
		return;
	}

	for (auto i = _pTarget->childList_.begin(); i != _pTarget->childList_.end(); i++)
	{
		Collision(*i);
	}
}

void GameObject::RoundRobin(GameObject* _pTarget)
{

	if (pCollider_ == nullptr)
		return;
	if (_pTarget->pCollider_ != nullptr)	//自分とターゲット
		Collision(_pTarget);
	//自分の子供全部とターゲット
	for (auto itr:_pTarget->childList_)
		RoundRobin(itr);
}

void GameObject::CollisionDraw()
{
	Direct3D::SetShader(SHADER_UNLIT);
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		(*i)->Draw(GetWorldPosition());
	}
	Direct3D::SetShader(SHADER_3D);
}
