#pragma once
namespace UDPClient
{
	//初期化
	void Initialize();

	//更新
	void Update();

	//ゲッター
	float GetMoveX();
	bool GetPlayerShotFlag();
	bool GetIsStart();
	bool GetIsLose();

	//セッター
	void SetMoveX(float posX);
	void SetEnemyShotFlag(bool bullet);
	void SetIsLose();
	void SetIsStart(bool startFlag);
};

