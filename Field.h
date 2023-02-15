#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

//◆◆◆を管理するクラス
class Field : public GameObject
{
    int hModel_[2];    //モデル番号
    struct
    {
        int type;
        int height;

    }table[15][15];
public:
    //コンストラクタ
    Field(GameObject* parent);

    //デストラクタ
    ~Field();

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

};