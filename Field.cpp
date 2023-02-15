#include "Field.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Field::Field(GameObject* parent)
    :GameObject(parent, "Field")
{

}

//デストラクタ
Field::~Field()
{
}

//初期化
void Field::Initialize()
{
    std::string fileName[] = { "Field","BoxBrick" };
    //モデルデータのロード
    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
    {
        std::string fn = "Assets/" + fileName[i] + ".fbx";
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
    }

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collision);
}

//更新
void Field::Update()
{

}

//描画
void Field::Draw()
{
   

    //for (int i = 0; i < 15; i++)
    //{
    //    for (int j = 0; j < 15; j++)
    //    {
    //        for (int k = 0; k < table[i][j].height + 1; k++)
    //        {
    //            //RayCastData data;

    //            //int type = table[i][j].type;
    //            Transform trans;
    //            trans.position_.x = i;
    //            trans.position_.z = j;
                Model::SetTransform(hModel_[0], transform_);
                Model::Draw(hModel_[0]);
    /*        }
        }
    }*/
}

//開放
void Field::Release()
{
}

//何かに当たった
void Field::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
}