#ifndef __FLYMEQUEUE_HPP
#define __FLYMEQUEUE_HPP
#include <stdio.h>
#include <pthread.h>
#include "ODSocket.h"

#define QUEUEL 20
#define IDENL 2
#define HEARTBEATL 2
#define RESL 2
#define IPPACL 20
#define SERVERLISTL 500
#define IPINFOL 200

ODSocket hostSocket;
ODSocket clientSocket;
char ips[QUEUEL][20];
int  total;
int  id[QUEUEL];
int	 number;
char serverList[SERVERLISTL];

bool isServer = false;
bool isClient = false;
bool start  = false;
char * centerServerIp="127.0.0.1";
char hostIp[20] = "blank";
char ownIP[20];

char clientIPS[10][20];
int  clientIPNumber;
char ipinfo[IPINFOL];
//获取自己主机的ip
void getOwnIP()
{
	char host[255];
	if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
	{
		printf("SOCKET_ERROR\n");
	}
	printf("%s\n", host);
	struct hostent *p = gethostbyname(host);
	if (p == NULL)
	{
		printf("p==NULL!\n");
	}
	else
	{
		int res = 0;
		for (int i = 0; p->h_addr_list[i] != 0; i++)
		{
			struct in_addr in;
			memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
			sprintf(ownIP, "%s", inet_ntoa(in));
			sprintf(ipinfo + res, "%2d", strlen(ownIP));
			res += 2;
			sprintf(ipinfo + res, "%s", ownIP);
			res += strlen(ownIP);
			printf("the %d IP is : %s\n", i , ownIP);
		}
		ipinfo[res] = 'E';
		ipinfo[res+1] = 'E';
		ipinfo[res+2] = '\0';
		printf("IPINFO=%s\n ", ipinfo);
		
	}
}
//转换函数
int  getIntFromChar(char* s,int len)
{
	int t = 0 ;
	for (int i = 0 ; i < len; ++i)
	{
		if(*(s+i) > '9' || *(s+i) < '0')
			t = t * 10;
		else
			t = (t*10) + (int)(*(s+i)-'0');
	}
	return t;
}
//解包获得ip
void getIP(int step, char * source, int len)
{
	for (int i = 0 ; i < len ; ++i)
	{
		ips[step][i] = *(source+i);
	}
	ips[step][len] = '\0';
}

//解包
void clientResolve()
{
	total = 0;
	int res = 0;
	int length;
	while(serverList[res] != 'E')
	{
		length = getIntFromChar(serverList + res , 2);
		res += 2;
		getIP(total, serverList+res, length);
		res += length;
		id[total] = getIntFromChar(serverList+res, 3);
		res += 3;
		++total;		
	}
}

void outputList()
{
	printf("There are totally %d servers waitting ：\n", total);
	for(int i = 0; i < total; ++i)
	{
		printf("No.%d:  ", i);
		printf("ip = %s ;", ips[i]);
		printf("serverId = %d \n", id[i]);
	}
	printf("select which server to connect(No.):");
}
void *clientFn(void * t)
{
	char res[RESL];
	char ip[IPPACL];
	while(isClient)
	{
		number = -1;
		if (clientSocket.Recv(serverList, SERVERLISTL, 0) < 0)
		{
			break;
		}
		clientResolve();
		outputList();
		while(number == -1 && isClient)
		{
			Sleep(500);
		}
		if (!isClient)
			break;
		sprintf(ip, "%3d", id[number]);
		if (clientSocket.Send(ip, IPPACL, 0) < 0)
		{
			break;
		}
		if (clientSocket.Recv(res, RESL, 0) < 0)
		{
			break;
		}
		else
		{
			if (res[0] =='S')
			{
				strcpy(hostIp, ips[number]);
				printf("START GAME BY SERVERIP=%s \n", hostIp);
				start = true;
				break;
			}
			else
			{
				printf("The Server which you has selected logged out\n   ");
			}
		}

	}
	clientSocket.Close();
	clientSocket.Clean();
	return 0;
}


void hostResolve()
{
	int res = 0 ;
	clientIPNumber = 0;
	int len = 0;
	while(ipinfo[res]!='E')
	{
		len = getIntFromChar(ipinfo + res, 2);
		printf("len = %d \n", len);
		res += 2;
		strncpy(clientIPS[clientIPNumber++],ipinfo+res, len);
		res += len;
	}
	for(int i = 0 ; i < clientIPNumber; ++i)
	{
		printf("i =%d; and IP=%s ; len = %d\n", i, clientIPS[i], strlen(clientIPS[i]));
	}
}
void *hostFn(void * t)
{
	char heart[HEARTBEATL];
	heart[0] = 'E';
	heart[1] = '\0';
	while(isServer)
	{
		if (hostSocket.Send(heart, HEARTBEATL, 0) < 0 )
		{
			break;		
		}
		if (hostSocket.Recv(heart, HEARTBEATL, 0) <= 0)
		{
			break;
		}
		if (heart[0] == 'S')
		{
			printf("Start GAME!\n");//开始游戏
			start = true;
			break;
		}
		if (heart[0] == 'H')
		{
			printf("HeartBeat Response\n");
		}
		if (!isServer)
			break;
		Sleep(1000);
		if (!isServer)
			break;
		Sleep(1000);
	}
	hostSocket.Close();
	hostSocket.Clean();
	return 0;
}



void startServer()
{
	isServer = true;
	hostSocket.Init();
	getOwnIP();//.init()里调用了 wasstartup(); 
	hostResolve();
	hostSocket.Create(AF_INET,SOCK_STREAM,0);
	hostSocket.Connect(centerServerIp,7880);
	hostSocket.Send("S",IDENL ,0);	
	hostSocket.Send(ipinfo, IPINFOL, 0);
	pthread_t tid;
	pthread_create(&tid, NULL , hostFn , NULL);
	//void * temp;
	//pthread_join(tid, &temp);	
}
void startClient()
{
	isClient = true;
	clientSocket.Init();
	clientSocket.Create(AF_INET,SOCK_STREAM,0);
	clientSocket.Connect(centerServerIp,7880);
	clientSocket.Send("C",IDENL ,0);	
	pthread_t tid;
	pthread_create(&tid, NULL , clientFn , NULL);
	//void * temp;
	//pthread_join(tid, &temp);
}
#endif
