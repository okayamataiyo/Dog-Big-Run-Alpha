#pragma once
//�C���N���[�h
#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

using std::string;
using std::list;

class SphereCollider;

/// <summary>
/// �S�ẴQ�[���I�u�W�F�N�g(�V�[�����܂߂�)���p������C���^�[�t�F�[�X
/// �Q�[���I�u�W�F�N�g�͐e�q�\���ɂȂ��Ă��āA
/// �}�g���N�X�̉e�����󂯂鎖�ɂȂ�
/// </summary>
class GameObject
{
	bool Is_DeadFlag;	//�����t���O

	
protected:
	list<GameObject*>	childList_;
	list<Collider*>		colliderList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;	//�I�u�W�F�N�g�̖��O�̔z��
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

	GameObject* FindChildObject(string _objName);
	GameObject* FindObject(string _objName);
	void AddCollider(Collider* _pCollider);
	void Collision(GameObject* _pTarget);
	void RoundRobin(GameObject* _pTarget);

	//�����ƏՓ˂����ꍇ�ɌĂ΂��(�I�[�o�[���C�h�p)
	//����:pTarget�Փ˂��Ă邩���ׂ鑊��
	virtual void OnCollision(GameObject* _pTarget) {};

	/// <summary>
	/// �e�X�g�p�̏Փ˔���g��\��
	/// </summary>
	void CollisionDraw();

	//�Z�b�^�[�E�Q�b�^�[
	void SetPosition(XMFLOAT3 _position);
	void SetPosition(float _x, float _y, float _z);
	void SetObjectName(string _s) { objectName_ = _s; }
	void SetTransform(Transform _transform) { transform_.position_ = _transform.position_; }

	/// <summary>
	/// �I�u�W�F�N�g�̖��O���擾
	/// </summary>
	/// <param name="">�I�u�W�F�N�g�̖��O</param>
	/// <returns>�I�u�W�F�N�g�̖��O</returns>
	const string& GetObjectName(void) const { return objectName_; }
	/// <summary>
	/// �ċA�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
	/// </summary>
	/// <returns>RootJob�̃A�h���X(GameObject*�^)</returns>
	GameObject* GetRootJob();
	/// <summary>
	/// �e�I�u�W�F�N�g���擾
	/// </summary>
	/// <returns></returns>
	GameObject* GetParent();
	/// <summary>
	/// ���[���h���W���擾
	/// </summary>
	/// <returns></returns>
	XMFLOAT3 GetWorldPosition() { return Transform::Float3Add(GetParent()->transform_.position_, transform_.position_); }

public:	//�e���v���[�g�̒�`
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

