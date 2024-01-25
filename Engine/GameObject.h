#pragma once
//インクルード
#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject
{
	bool Is_DeadFlag;	//消去フラグ

	
protected:
	list<GameObject*>	childList_;
	list<Collider*>		colliderList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;	//オブジェクトの名前の配列
	Collider*		pCollider_;

public:
	GameObject();
	GameObject(GameObject* _parent, const std::string& _name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() =0;
	virtual void Release() =0;
	bool IsDead();
	void KillMe();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	//セッター・ゲッター
	void SetPosition(XMFLOAT3 _position);
	void SetPosition(float _x, float _y, float _z);	
	void SetObjectName(string _s) { objectName_ = _s; }

	/// <summary>
	/// オブジェクトの名前を取得
	/// </summary>
	/// <param name="">オブジェクトの名前</param>
	/// <returns>オブジェクトの名前</returns>
	const string& GetObjectName(void) const { return objectName_; }
	GameObject* GetRootJob();
	/// <summary>
	/// 親オブジェクトを取得
	/// </summary>
	/// <returns></returns>
	GameObject* GetParent();

	XMFLOAT3 GetWorldPosition() { return Transform::Float3Add(GetParent()->transform_.position_, transform_.position_); }
	GameObject* FindChildObject(string _objName);
	GameObject* FindObject(string _objName);
	void AddCollider(Collider* _pCollider);
	void Collision(GameObject* _pTarget);
	void RoundRobin(GameObject* _pTarget);

	//何かと衝突した場合に呼ばれる(オーバーライド用)
	//引数:pTarget衝突してるか調べる相手
	virtual void OnCollision(GameObject* _pTarget) {};


public:	//テンプレートの定義
	template <class T>
	T* Instantiate(GameObject* _parent)
	{
		T* pObject;
		pObject = new T(_parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};

