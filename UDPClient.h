#pragma once
namespace UDPClient
{
	//������
	void Initialize();

	//�X�V
	void Update();

	//�Q�b�^�[
	float GetMoveX();
	bool GetPlayerShotFlag();
	bool GetIsStart();
	bool GetIsLose();

	//�Z�b�^�[
	void SetMoveX(float posX);
	void SetEnemyShotFlag(bool bullet);
	void SetIsLose();
	void SetIsStart(bool startFlag);
};

