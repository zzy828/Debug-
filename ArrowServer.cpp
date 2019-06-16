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

typedef struct myPara //��������ṹ��ֻ��Ϊ�˷��㴫������������߳��Ա�debug
{
	SOCKET ClientSocket;
	sockaddr_in clntAddr;
	int id;
}MyPara;

DWORD WINAPI MyThreadPro(const LPVOID param)//���߳�ִ�к���
{
	MyPara *temp = (MyPara*)param;
	/*
	int my_id = temp->id;
	cout << my_id << "�̣߳����Կ�ʼ, �ȴ��ͻ��˷������ݡ� id��ַ��" << &(temp->id) << " �ͻ��˶˿ں�:" << ntohs(temp->clntAddr.sin_port) << endl;

	//�ӿͻ��˽�������
	char szBuffer[MAXBYTE] = { 0 };
	
	while(1) recv(temp->ClientSocket, (char *)(test), sizeof(test), NULL);
	//memcpy(&test, szBuffer, sizeof(test));

	//cout << my_id << "�̣߳��ӿͻ��˽��ܵ�:" << test.a << " " << test.b << " " << test.c << " " << test.d << " " << test.flag << " temp->id:" << temp->id << " �ͻ��˶˿ں�:" << ntohs(temp->clntAddr.sin_port) << endl;

	//��ͻ��˷�������  
	char *str = "������Ƿ�����";
	send(temp->ClientSocket, str, strlen(str) + sizeof(char), NULL);
	cout << my_id << "�̣߳��ɹ���ͻ��˷�������" << " temp->id:" << temp->id << " �ͻ��˶˿ں�:" << ntohs(temp->clntAddr.sin_port) << endl;
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
WSADATA wsaData;//��ʼ��dll 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽��� 
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, 0);
	//���ø�������Ȼ����׽��ְ���һ��
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(5256);
	bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

	//����̵߳ľ��

	HANDLE hThread[5];
	listen(servSock, 20);
	for (int i = 0; i < 5; i++)
	{
		
		MyPara *temp = new MyPara;
		sockaddr_in clntAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize);
		cout << "�ͻ��� : " << i + 1 << " ������Ϸ!" << endl;
		allRound = i + 1;
		char p = i ;
		send(clntSock, (char *)(&p), 1, 0);
		temp->ClientSocket = clntSock;
		temp->id = i;
		temp->clntAddr = clntAddr;
		hThread[i] = CreateThread(NULL, 0, &MyThreadPro, temp, 0, NULL);
	}
	WaitForMultipleObjects(5, hThread, TRUE, INFINITE);
	//�ر��׽���  
	closesocket(servSock);
	cout << "���пͻ����Ѿ��˳���" << endl;
	system("pause");
	//��ֹ DLL ��ʹ��  
	WSACleanup();
	return 0;
}

