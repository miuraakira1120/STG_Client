//#include "Base.h"
//#include "Engine/Input.h"
//#include "Engine/Model.h"
//#include "Engine/Camera.h"
//
////コンストラクタ
//Base::Base(GameObject* parent)
//    :GameObject(parent, "Base")
//{
//
//}
//
////デストラクタ
//Base::~Base()
//{
//}
//
////初期化
//void Base::Initialize()
//{
//    std::string fileName[] = { "BoxBrick" };
//    //モデルデータのロード
//    //for (int i = 0; i < /*sizeof(fileName)*/2; i++)
//    //{
//        std::string fn = "Assets/" + fileName[0] + ".fbx";
//        hModel_[0] = Model::Load(fn);
//        assert(hModel_[0] >= 0);
//    //}
//}
//
////更新
//void Base::Update()
//{
//
//}
//
////描画
//void Base::Draw()
//{
//
//
//    //for (int i = 0; i < 15; i++)
//    //{
//    //    for (int j = 0; j < 15; j++)
//    //    {
//    //        for (int k = 0; k < table[i][j].height + 1; k++)
//    //        {
//    //            //RayCastData data;
//
//    //            //int type = table[i][j].type;
//    //            Transform trans;
//    //            trans.position_.x = i;
//    //            trans.position_.z = j;
//    Model::SetTransform(hModel_[0], transform_);
//    Model::Draw(hModel_[0]);
//    /*        }
//        }
//    }*/
//}
//
////開放
//void Base::Release()
//{
//}
//
