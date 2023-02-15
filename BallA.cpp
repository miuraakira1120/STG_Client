//#include "Ball.h"
//#include "Engine/Model.h"
//
////コンストラクタ
//Ball::Ball(GameObject* parent)
//	: GameObject(parent, "Ball")
//{
//}
//
////デストラクタ
//Ball::~Ball()
//{
//}
//
////初期化
//void Ball::Initialize()
//{
//    std::string fileName[] = { "BoxDefault","WhiteBall"};
//    //モデルデータのロード
//    for (int i = 0; i < /*sizeof(fileName)*/2; i++)
//    {
//        std::string fn = "Assets/" + fileName[i] + ".fbx";
//        hModel_[i] = Model::Load(fn);
//        assert(hModel_[i] >= 0);
//    }
//
//    transform_.scale_ = XMFLOAT3(5.0f, 5.0f, 5.0f);
//}
//
////更新
//void Ball::Update()
//{
//	//GameObject* Title = FindObject("SceneManager");
//    //transform_.position_.y += 0.1f;
//}
//
////描画
//void Ball::Draw()
//{
//    Transform trans;
//   
//
//    Model::SetTransform(hModel_[RED], trans);
//    Model::Draw(hModel_[RED]);
//
//    trans.position_.x = 3;
//    //trans.position_.y = 3;
//    trans.position_.z = 3;
//    Model::SetTransform(hModel_[WHITE], trans);
//    Model::Draw(hModel_[WHITE]);
//}
//
////開放
//void Ball::Release()
//{
//}