#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPClient.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player")
{

}

//デストラクタ
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("PlayerBone.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = -7;
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    damage = 0;
}

//更新
void Player::Update()
{
    if (UDPClient::GetPlayerShotFlag())
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(0);//0はプレイヤー、1は敵
        pBall->SetPosition(transform_.position_);
    }
    transform_.position_.x = UDPClient::GetMoveX();
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Player::Release()
{
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
}

void Player::Damage(int damage_)
{
    damage += damage_;

    if (damage >= HP)
    {
        KillMe();
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }
}