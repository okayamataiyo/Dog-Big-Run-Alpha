#pragma once
//インクルード
#include "Engine/GameObject.h"
#include "Controller.h"
#include "Sky.h"

/// <summary>
/// 遊べるシーン
/// </summary>
class PlayScene : public GameObject
{
private:
    //メンバ
    Sky* pSky_;

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    PlayScene();
    PlayScene(GameObject* _pParent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

