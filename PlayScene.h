#pragma once
#include "Engine/GameObject.h"
#include "Engine/Camera.h"
#include "Player.h"

/// <summary>
/// 遊べるシーン
/// </summary>
class PlayScene :
    public GameObject
{
private:
    //メンバ変数
    Player* pPlayer_[1];
    Camera* pCamera_;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="parent">親オブジェクト</param>
    PlayScene(GameObject* _parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

