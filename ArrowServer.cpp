//simpleServer.cpp
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<process.h>
#include<iostream>
#pragma comment (lib, "ws2_32.lib")

using namespace std;
//MTCMutex mLOCK;
struct ArrowMessage {
	unsigned char fire;
	unsigned char weapRank;
	unsigned char weapKind;
	unsigned char picKind;
	char HP;
	bool Ai;
	float rotation;
	float x, y;
	ArrowMessage() {
		fire = 0;
		weapRank = 1;
		weapKind = 1;
		picKind = 1;
		HP = 100;
		Ai = false;
		rotation = 0.0;
		x = 800.0f;
		y = 800.0f;
	}
	ArrowMessage& operator = (const ArrowMessage &rhs) {
		fire = rhs.fire;
		weapRank = rhs.weapRank;
		weapKind = rhs.weapKind;
		picKind = rhs.picKind;
		HP = rhs.HP;
		Ai = rhs.Ai;
		rotation = rhs.rotation;
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
}mess[5][4];
int allRound = 0;
bool beFiring[5][5][4];
struct Test {
	int a, b;
	float c, d;
	char flag;
}test[10];

typedef struct myPara //我设这个结构体只是为了方便传更多参数到子线程以便debug
{
	SOCKET ClientSocket;
	sockaddr_in clntAddr;
	int id;
}MyPara;

DWORD WINAPI MyThreadPro(const LPVOID param)//子线程执行函数
{
	MyPara *temp = (MyPara*)param;
	/*
	int my_id = temp->id;
	cout << my_id << "线程：测试开始, 等待客户端发送数据。 id地址：" << &(temp->id) << " 客户端端口号:" << ntohs(temp->clntAddr.sin_port) << endl;

	//从客户端接受数据
	char szBuffer[MAXBYTE] = { 0 };
	
	while(1) recv(temp->ClientSocket, (char *)(test), sizeof(test), NULL);
	//memcpy(&test, szBuffer, sizeof(test));

	//cout << my_id << "线程：从客户端接受到:" << test.a << " " << test.b << " " << test.c << " " << test.d << " " << test.flag << " temp->id:" << temp->id << " 客户端端口号:" << ntohs(temp->clntAddr.sin_port) << endl;

	//向客户端发送数据  
	char *str = "你好我是服务器";
	send(temp->ClientSocket, str, strlen(str) + sizeof(char), NULL);
	cout << my_id << "线程：成功向客户端发送数据" << " temp->id:" << temp->id << " 客户端端口号:" << ntohs(temp->clntAddr.sin_port) << endl;
	*/
	ArrowMessage messt[4], mes[5][4];
	cout << temp->id << endl;
	while (true) {
		//mLOCK.Lock();

		recv(temp->ClientSocket, (char *)(messt), sizeof(messt), 0);
		//cout << int(messt[2].HP) << "~" << endl;
		//cout << int(messt->fire) << endl;
		//mLOCK.UnLock();
		if (messt->fire == 20) {
			break;
		}
		else if (messt->fire == 10) {
			char p = allRound;
			//cout << allRound << "*" << endl;
			send(temp->ClientSocket, (char *)(&p), 1, 0);
			memcpy(mes, mess, sizeof(mess));
			for (int i = 0; i < allRound; ++i) {
				for (int j = 0; j < 4; ++j) {
					if (beFiring[temp->id][i][j]) {
						mes[i][j].fire = true;
						beFiring[temp->id][i][j] = false;
					}
				}
			}
			send(temp->ClientSocket, (char *)(mes[0]), sizeof(mes), 0);
		}
		else {
			//mLOCK.Lock();
			for (int i = 0; i < 4; ++i) {
				mess[temp->id][i] = messt[i];
				//if(messt[i])
				if (mess[temp->id][i].fire) {
					for (int j = 0; j < allRound; ++j) {
						if (j != temp->id) {
							beFiring[j][temp->id][i] = true;
						}
					}
				}
			}
			//mLOCK.UnLock();

		}
		//mLOCK.UnLock();

	}
	return 0;
}

int main()
{
WSADATA wsaData;//初始化dll 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字 
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);
	//设置各种条件然后和套接字绑定在一起
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(5256);
	bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

	//获得线程的句柄

	HANDLE hThread[5];
	listen(servSock, 20);
	for (int i = 0; i < 5; i++)
	{
		
		MyPara *temp = new MyPara;
		sockaddr_in clntAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize);
		cout << "客户端 : " << i + 1 << " 加入游戏!" << endl;
		allRound = i + 1;
		char p = i ;
		send(clntSock, (char *)(&p), 1, 0);
		temp->ClientSocket = clntSock;
		temp->id = i;
		temp->clntAddr = clntAddr;
		hThread[i] = CreateThread(NULL, 0, &MyThreadPro, temp, 0, NULL);
	}
	WaitForMultipleObjects(5, hThread, TRUE, INFINITE);
	//关闭套接字  
	closesocket(servSock);
	cout << "所有客户端已经退出！" << endl;
	system("pause");
	//终止 DLL 的使用  
	WSACleanup();
	return 0;
}

