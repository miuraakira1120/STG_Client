#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPClient.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy")
{

}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化
void Enemy::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = 5;
    transform_.rotate_.y = 180;
    damage = 0;

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    //Camera::SetPosition(XMFLOAT3)
}

//更新
void Enemy::Update()
{
    //+-13
    XMFLOAT3 LeftStick = Input::GetPadStickL();
    LeftStick.x /= 10;
    /*transform_.position_.x += LeftStick.x;
    transform_.position_.z += LeftStick.y;*/

    XMFLOAT3 move = { LeftStick.x,0,0 }; //移動量
    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

    //vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

    XMStoreFloat3(&transform_.position_, vPos);


    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        //Instantiate<bullet>(GetParent());//()の中は親
        pBall = Instantiate<Ball>(GetParent());
        //親からハート発射
        pBall->SetPosition(transform_.position_);
    }

    //D押したら右
    if (Input::IsKey(DIK_RIGHT))
    {
        if (transform_.position_.x < MAX_X)
        {
            XMFLOAT3 move = { -Enemy_MOVE,0,0 }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }
    //A押したら
    if (Input::IsKey(DIK_LEFT))
    {
        if (transform_.position_.x > -MAX_X)
        {
            XMFLOAT3 move = { Enemy_MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列
            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove;

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }

    if (Input::IsKeyDown(DIK_RETURN))
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(1);//0はプレイヤー、1は敵
        pBall->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z - 2);
        UDPClient::SetEnemyShotFlag(true);
    }
    else
    {
        UDPClient::SetEnemyShotFlag(false);
    }
    UDPClient::SetMoveX(transform_.position_.x);
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Enemy::Release()
{
}

//何かに当たった
void Enemy::OnCollision(GameObject* pTarget)
{

    /*if (pTarget->GetObjectName() == "Ball")
    {
        pTarget->KillMe();
        damage++;

        if (damage >= HP)
        {

            KillMe();
        }
    }*/

}

void Enemy::Damage(int damage_)
{
     damage += damage_;

     if (damage >= HP)
     {
         UDPClient::SetIsLose();
         KillMe();
         SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
         pSceneManager->ChangeScene(SCENE_ID_RESULT);
     }
}

