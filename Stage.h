#pragma once
//�C���N���[�h
#include <string>
#include "Engine/GameObject.h"

using std::string;
//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    string ModelName_[2] = { "Assets/Ground.fbx","Assets/Sky.fbx" };
public:
    //�R���X�g���N�^
    //����:parent �e�I�u�W�F�N�g(SceneManager)
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
    //����:x,z  ���ׂ�ʒu
    //�߂�l:�ʂ�Ȃ�=true/�ʂ�Ȃ�=false
    //bool IsWall(int x, int z);

    int GetModelHandle() { return hModel_; }
};