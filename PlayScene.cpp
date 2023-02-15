#include "PlayScene.h"
#include"Player.h"
#include "Ball.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Enemy.h"
#include "Engine/Camera.h"
#include "Stage.h"
#include "UDPClient.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Stage>(this);
	time = 1;
	Camera::SetPosition(XMFLOAT3(0, 25, 10));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
}

//更新
void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_1))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (time <= 0)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}