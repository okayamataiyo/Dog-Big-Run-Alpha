#pragma once
//インクルード
#include "Engine/GameObject.h"
#include "Player.h"

/// <summary>
/// 遊べるシーン
/// </summary>
class PlayScene :
    public GameObject
{
private:
    //メンバ変数
    Player* pPlayer_[2];
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

