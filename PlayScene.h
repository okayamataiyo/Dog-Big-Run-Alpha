#pragma once
//�C���N���[�h
#include "Engine/GameObject.h"
#include "Controller.h"
#include "Sky.h"

/// <summary>
/// �V�ׂ�V�[��
/// </summary>
class PlayScene : public GameObject
{
private:
    //�����o
    Sky* pSky_;

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    PlayScene();
    PlayScene(GameObject* _pParent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

