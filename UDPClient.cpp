#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPClient.h"

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>



#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// �T�[�o�̃|�[�g�ԍ�

const  char* SERVERIPADDRESS = "127.0.0.1";


SOCKET sock;
WSADATA wsaData;

SOCKADDR_IN serverAddr;
SOCKADDR_IN fromAddr;

float enemyPosX = 0;
float moveTransX = 0;
//float playerPosY;
//float playerPosZ;

bool playerShotFlag = false;
bool enemyShotFlag = false;

bool isStart = true;
bool recvIsStart = false;

bool isWin = false;
bool isLose = false;

void UDPClient::Initialize()
{
	// WinSock�̏�����	WSAStartup()
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// error
	}
	// UDP�\�P�b�g�̍쐬	socket()
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// error
	}


	//�m���u���b�L���O���[�h
	u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);
}

void UDPClient::Update()
{

	//�A�h���X�Ƃ��|�[�g�ݒ�
   // �T�[�o�̃A�h���X���Z�b�g

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));							// 0�N���A�ŏ�����
	serverAddr.sin_family = AF_INET;									// IPv4�A�h���X�g�p
	serverAddr.sin_port = htons(PORT);						    // �|�[�g�ԍ��w��
	inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

	////////////////���M////////////////////////////
	//�}�C�i�X�̒l�������Ȃ�����
	enemyPosX += 1000;
	int sendValue = htonf(enemyPosX);
	int rettt = sendto(sock, (char*)&sendValue, sizeof(sendValue), 0, (SOCKADDR*)&serverAddr,sizeof(serverAddr));

	int sendEnemyShotFlag = htonl((long)enemyShotFlag);
	int rettt2 = sendto(sock, (char*)&sendEnemyShotFlag, sizeof(sendEnemyShotFlag), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		int sendStartFlag = htonl((long)isStart);
		int rettt3 = sendto(sock, (char*)&sendStartFlag, sizeof(sendStartFlag), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//////////////////��M/////////////////////////////
	// ���M���̃A�h���X�����i�[����\�P�b�g�A�h���X�\����
	int recvCount;
	int fromlen = sizeof(serverAddr);

	// buff�Ɏ�M������������i�[
	int ret = recvfrom(sock, (char*)&recvCount, sizeof(recvCount), 0, (SOCKADDR*)&serverAddr, &fromlen);
	if (ret < 0)
	{
		//error
	}
	else
	{
		// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������
		moveTransX = ntohf(recvCount);
		moveTransX -= 1000;
	}

	int recvPlayerShotFlag;
	int fromlen2 = sizeof(serverAddr);

	// ��M������������i�[
	int ret2 = recvfrom(sock, (char*)&recvPlayerShotFlag, sizeof(recvPlayerShotFlag), 0, (SOCKADDR*)&serverAddr, &fromlen2);
	if (ret2 < 0)
	{
		//error
	}
	else
	{
		// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������	
		playerShotFlag = ntohl(recvPlayerShotFlag);
	}

	int recvStartFlag;
	int fromlen3 = sizeof(fromAddr);

	// ��M������������i�[
	int ret3 = recvfrom(sock, (char*)&recvStartFlag, sizeof(recvStartFlag), 0, (SOCKADDR*)&serverAddr, &fromlen3);
	if (ret3 < 0)
	{
		//error
	}
	else
	{
		// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������	
		recvIsStart = ntohl(recvStartFlag);
	}
	
///////////////////////////////////////////////////////////
}

float UDPClient::GetMoveX()
{
	return moveTransX;
}

void UDPClient::SetMoveX(float posX)
{
	enemyPosX = posX;
}

bool UDPClient::GetPlayerShotFlag()
{
	return playerShotFlag;
}

void UDPClient::SetEnemyShotFlag(bool bullet)
{
	enemyShotFlag = bullet;
}

bool UDPClient::GetIsStart()
{
	return recvIsStart;
}

bool UDPClient::GetIsLose()
{
	return isLose;
}

void UDPClient::SetIsLose()
{
	isLose = true;
}

void UDPClient::SetIsStart(bool startFlag)
{
	isStart = startFlag;
}
