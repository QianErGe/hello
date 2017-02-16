/*
 * socket 封装client端
 * 1 先实现简单的socket通信
 * 2 再封装http请求
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
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
#define MAX_SIZE 1024
void vSend( int client_fd );

int main()
{
	cout << "now client is begin ..." << endl;
	// 1 创建socket描述符
	int client_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( client_fd == -1)
	{
		perror("create error ...");
		exit(-1);
	}

	// 2 向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;  // 使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");// 具体的IP地址
    serv_addr.sin_port = htons(8888);  //端口
    int iRes = 0;
    
    // 3 CONNET
    iRes = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if ( iRes < 0 )
    {
    	perror(" connect error ...");
    	exit(-1);
    }

    // 4 send
	vSend( client_fd );
#if 0
	char szBuf[MAX_SIZE+1] = {0};
    while(1)
    {
    	cin >>  szBuf;
	    iRes = send( client_fd, szBuf, sizeof(szBuf), 0) ;
	    if ( iRes < 0 )
	    {
	    	perror("send error...");
	    	exit(-1);
	    }

	    // 5 recv
	    iRes = recv( client_fd, szBuf, sizeof(szBuf),0);
	    if (iRes > 0)
	    {
	    	printf(" this is from server :%s\n", szBuf );
	    	if (strcmp(szBuf, "byebye") == 0)
			{
				printf("%s\n", "now exit...");
				close(client_fd);
				return 0;
			}
	    }
	    printf(" now please reply...");
    }
#endif
    close(client_fd);
	return 0;
}
void vSend( int client_fd )
{
	int iRes = 0;
    char szBuf[MAX_SIZE] = {0};
	int i = 3;
	while(1)
    {
		cin >> szBuf;
		send( client_fd, szBuf, sizeof(szBuf), 0 );// 模仿CIP header
		recv( client_fd, szBuf, sizeof(szBuf),0 );
		cout << "server say:" << szBuf << endl;
	

	// 然后将多包数据进行发送
		while(i)
		{
			i--;
			cin >> szBuf;
			iRes = send(client_fd, szBuf, sizeof(szBuf), 0);
			if ( iRes < 0 )
			{
				perror("send error...");
				exit(-1);
			}
		}
		cout << "over ... wait for server" << endl;
	    // 5 recv 收取服务端的反馈
		while(1)
		{

		memset( szBuf, 0, sizeof(szBuf) );
	    iRes = recv( client_fd, szBuf, sizeof(szBuf),0 );
	    if (iRes > 0)
	    {
			
			printf(" this is from server :%s\n", szBuf );
	    	if (strcmp(szBuf, "byebye") == 0)
			{
				printf("%s\n", "now exit...");
				close(client_fd);
				return ;
			}
		printf(" 收到最终回复:%s...:%d", szBuf, iRes);
	    break;
		}
		}
		break;
    }
    
}
