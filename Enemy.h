#pragma once
#include "Engine/GameObject.h"
#include "Ball.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;    //モデル番号

    const int HP = 3;
    const float RETURN_MOVE = 0.01f;
    const float Enemy_MOVE = 0.1f;//移動距離
    const float MAX_X = 15;
    int damage;
    Ball* pBall = (Ball*)FindObject("Ball");
public:
    int EnemyID;

    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
   //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    void Damage(int damage);
};