/* 简单的socket例子，
 * 1 先实现简单的服务端与客户端的网络通信
 * 2 后续实现 使用http协议包装信息
 * date 2016-07-08
 * writer by zhaoq
*/ 
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;

#define PORT 8888
#define QUEUE 5
#define BUFSIZE 1024

int main()
{

	cout << "now server is already..." << endl;
	// 1 创建socket
	int server_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( server_fd == -1)
	{
		perror("create error ...");
		exit(-1);
	}

	// 2 地址
	struct sockaddr_in server_addr;
	server_addr.sin_family      = AF_INET;
	server_addr.sin_port        = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

	// 3 绑定 成功返回0，错误返回－1
	int iRes = 0;
	iRes = bind( server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr) );
	if ( iRes == -1 )
	{
		perror("bind error...");
		exit(-1);
	}
	
	// 4 listen，成功返回0，错误返回－1
	iRes = listen( server_fd, 5 );
	if ( iRes == -1 )
	{
		perror("listen error ...");
		exit(-1);
	}

	// 5 accept
	int iConnetFd = accept( server_fd, NULL, NULL );
	if ( iConnetFd == -1 )
	{
		perror("accept error ...");
		exit(-1);
	}

	char szBuf[BUFSIZE+1] = {0};
	while(1)
	{
		// 6 read buf
		memset( szBuf, 0, sizeof(szBuf) );
		iRes = recv( iConnetFd, szBuf, sizeof(szBuf), 0);
		if ( iRes > 0 )
		{
			if (strcmp(szBuf, "byebye") == 0)
			{
				printf("%s\n", "now exit...");
				close(iConnetFd);
				close(server_fd);
				return 0;
			}
			printf(" this is from client:%s\n", szBuf);
			printf(" now please reply...");
			memset( szBuf, 0, sizeof(szBuf) );
			scanf("%s", szBuf);
			send( iConnetFd, szBuf, sizeof(szBuf), 0 );
		}
		// printf(" no client ...");
	}

	close(iConnetFd);
	close(server_fd);
	return 0;
}
