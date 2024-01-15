#include "Engine/Model.h"
#include "Engine/Sprite.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Stage.h"

Transform trans_G;
Transform trans_A;
Transform trans_B;
Transform trans_L;

namespace 
{
    const XMFLOAT4 DEF_LIGHT_POSITION{ 1,2,1,0 };

}

void Stage::IntConstantBuffer()
{
    //コンスタントバッファに情報を渡す
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    //コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1, -1, -1,-1},lightSourcePosition_(DEF_LIGHT_POSITION)
{
    Sprite* s;

}

//デストラクタ
Stage::~Stage()
{

}

//初期化
void Stage::Initialize()
{

    //モデルデータのロード
    hModel_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hModel_[0] >= 0);

    hModel_[1] = Model::Load("Assets/Ground.fbx");
    assert(hModel_[1] >= 0);

    hModel_[2] = Model::Load("Assets/BallNormal02.fbx");
    assert(hModel_[2] >= 0);


    hModel_[3] = Model::Load("Assets/Pipe.fbx");
    assert(hModel_[3] >= 0);

    IntConstantBuffer();
}

//更新
void Stage::Update()
{
    trans_A.rotate_.z = 90;
    trans_A.scale_.y = 0.4;
    trans_A.position_.y = 0.5;
    trans_G.position_.y = 0;
    trans_B.position_.x = 2;
    trans_B.position_.z = 2;
    trans_B.position_.y = 1;
    trans_B.rotate_.y += 1;
    trans_L.scale_ = { 0.2,0.2,0.2 };
    //trans_B.rotate_.y += 0.5;

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());
    Direct3D::pContext_->UpdateSubresource(pCBStageScene_,0, NULL,&cb,0,0); 
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);//頂点シェーダー
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);//ピクセルシェーダー

    XMFLOAT4 LightPos = { 0,0,0,0 };
    XMFLOAT4 Margin   = { 0,0,0,0 };

    if (Input::IsKey(DIK_UP))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x,LightPos.y + 0.1f,LightPos.z,LightPos.w};
        SetLightPos(Margin);
    }
    if (Input::IsKey(DIK_DOWN))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x,LightPos.y - 0.1f,LightPos.z,LightPos.w };
        SetLightPos(Margin);
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x + 0.1f,LightPos.y,LightPos.z,LightPos.w };
        SetLightPos(Margin);
    }
    if (Input::IsKey(DIK_LEFT))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x - 0.1f,LightPos.y,LightPos.z,LightPos.w };
        SetLightPos(Margin);
    }



    if (Input::IsKey(DIK_W))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x,LightPos.y,LightPos.z + 0.1f,LightPos.w };
        SetLightPos(Margin);
    }

    if (Input::IsKey(DIK_S))
    {
        LightPos = GetLightPos();
        Margin = { LightPos.x,LightPos.y,LightPos.z - 0.1f,LightPos.w };
        SetLightPos(Margin);
    }

    if (Input::IsMouseButton(0))
    {
        trans_L.rotate_.y += 1.0f;
    }

    if (Input::IsMouseButton(1))
    {
        trans_L.rotate_.y -= 1.0f;
    }

    XMFLOAT4 tmp{ GetLightPos() };
    trans_L.position_ = { tmp.x,tmp.y,tmp.z };

}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_[0], trans_A);
    Model::Draw(hModel_[0]);

    //Model::SetTransform(hModel_[1], trans_G);
    //Model::Draw(hModel_[1]);

    Model::SetTransform(hModel_[2], trans_B);
    Model::Draw(hModel_[2]);

    Model::SetTransform(hModel_[3], trans_L);
    Model::Draw(hModel_[3]);
}

//開放
void Stage::Release()
{
}