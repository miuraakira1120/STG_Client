#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPClient.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy")
{

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//������
void Enemy::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = 5;
    transform_.rotate_.y = 180;
    damage = 0;

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    //Camera::SetPosition(XMFLOAT3)
}

//�X�V
void Enemy::Update()
{
    //+-13
    XMFLOAT3 LeftStick = Input::GetPadStickL();
    LeftStick.x /= 10;
    /*transform_.position_.x += LeftStick.x;
    transform_.position_.z += LeftStick.y;*/

    XMFLOAT3 move = { LeftStick.x,0,0 }; //�ړ���
    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

    //vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

    XMStoreFloat3(&transform_.position_, vPos);


    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        //Instantiate<bullet>(GetParent());//()�̒��͐e
        pBall = Instantiate<Ball>(GetParent());
        //�e����n�[�g����
        pBall->SetPosition(transform_.position_);
    }

    //D��������E
    if (Input::IsKey(DIK_RIGHT))
    {
        if (transform_.position_.x < MAX_X)
        {
            XMFLOAT3 move = { -Enemy_MOVE,0,0 }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }
    //A��������
    if (Input::IsKey(DIK_LEFT))
    {
        if (transform_.position_.x > -MAX_X)
        {
            XMFLOAT3 move = { Enemy_MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��
            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove;

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }

    if (Input::IsKeyDown(DIK_RETURN))
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(1);//0�̓v���C���[�A1�͓G
        pBall->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z - 2);
        UDPClient::SetEnemyShotFlag(true);
    }
    else
    {
        UDPClient::SetEnemyShotFlag(false);
    }
    UDPClient::SetMoveX(transform_.position_.x);
}

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Enemy::Release()
{
}

//�����ɓ�������
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

