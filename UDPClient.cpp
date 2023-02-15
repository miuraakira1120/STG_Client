#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPClient.h"

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>



#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// サーバのポート番号

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
	// WinSockの初期化	WSAStartup()
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// error
	}
	// UDPソケットの作成	socket()
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// error
	}


	//ノンブロッキングモード
	u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);
}

void UDPClient::Update()
{

	//アドレスとかポート設定
   // サーバのアドレス情報セット

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));							// 0クリアで初期化
	serverAddr.sin_family = AF_INET;									// IPv4アドレス使用
	serverAddr.sin_port = htons(PORT);						    // ポート番号指定
	inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

	////////////////送信////////////////////////////
	//マイナスの値を入れられないから
	enemyPosX += 1000;
	int sendValue = htonf(enemyPosX);
	int rettt = sendto(sock, (char*)&sendValue, sizeof(sendValue), 0, (SOCKADDR*)&serverAddr,sizeof(serverAddr));

	int sendEnemyShotFlag = htonl((long)enemyShotFlag);
	int rettt2 = sendto(sock, (char*)&sendEnemyShotFlag, sizeof(sendEnemyShotFlag), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		int sendStartFlag = htonl((long)isStart);
		int rettt3 = sendto(sock, (char*)&sendStartFlag, sizeof(sendStartFlag), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//////////////////受信/////////////////////////////
	// 送信元のアドレス情報を格納するソケットアドレス構造体
	int recvCount;
	int fromlen = sizeof(serverAddr);

	// buffに受信した文字列を格納
	int ret = recvfrom(sock, (char*)&recvCount, sizeof(recvCount), 0, (SOCKADDR*)&serverAddr, &fromlen);
	if (ret < 0)
	{
		//error
	}
	else
	{
		// とても大事な処理 ... 多バイトデータだから
		moveTransX = ntohf(recvCount);
		moveTransX -= 1000;
	}

	int recvPlayerShotFlag;
	int fromlen2 = sizeof(serverAddr);

	// 受信した文字列を格納
	int ret2 = recvfrom(sock, (char*)&recvPlayerShotFlag, sizeof(recvPlayerShotFlag), 0, (SOCKADDR*)&serverAddr, &fromlen2);
	if (ret2 < 0)
	{
		//error
	}
	else
	{
		// とても大事な処理 ... 多バイトデータだから	
		playerShotFlag = ntohl(recvPlayerShotFlag);
	}

	int recvStartFlag;
	int fromlen3 = sizeof(fromAddr);

	// 受信した文字列を格納
	int ret3 = recvfrom(sock, (char*)&recvStartFlag, sizeof(recvStartFlag), 0, (SOCKADDR*)&serverAddr, &fromlen3);
	if (ret3 < 0)
	{
		//error
	}
	else
	{
		// とても大事な処理 ... 多バイトデータだから	
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
