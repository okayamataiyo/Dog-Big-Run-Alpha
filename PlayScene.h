#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"
#include "Player.h"

/// <summary>
/// �V�ׂ�V�[��
/// </summary>
class PlayScene :
    public GameObject
{
private:
    //�����o�ϐ�
    Player* pPlayer_[1];
    Camera* pCamera_;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="parent">�e�I�u�W�F�N�g</param>
    PlayScene(GameObject* _parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

