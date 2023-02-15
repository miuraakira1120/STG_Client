#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Ball.h"

//◆◆◆を管理するクラス
class Ball : public GameObject
{
    int hModel_;    //モデル番号
    int bulletType;

public:
    int ballID;
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

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

    //ゲッター
    int GetBulletType();

    //セッター
    void SetBulletType(int type);
};