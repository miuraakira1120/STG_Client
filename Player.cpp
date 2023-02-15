#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPClient.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player")
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("PlayerBone.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = -7;
    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    damage = 0;
}

//�X�V
void Player::Update()
{
    if (UDPClient::GetPlayerShotFlag())
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(0);//0�̓v���C���[�A1�͓G
        pBall->SetPosition(transform_.position_);
    }
    transform_.position_.x = UDPClient::GetMoveX();
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Player::Release()
{
}

//�����ɓ�������
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