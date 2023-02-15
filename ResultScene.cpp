#include "ResultScene.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "UDPClient.h"

int ResultScene::mode;

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_()
{
}
//初期化
void ResultScene::Initialize()
{
	//画像データのロード
	hPict_[0] = Image::Load("youWin.jpg");
	assert(hPict_ >= 0);

	//画像データのロード
	hPict_[1] = Image::Load("youLose.jpg");
	assert(hPict_ >= 0);
}

//更新
void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//描画
void ResultScene::Draw()
{
	if (!UDPClient::GetIsLose())
	{
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
	}
	else
	{
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);
	}
}

//開放
void ResultScene::Release()
{
}

