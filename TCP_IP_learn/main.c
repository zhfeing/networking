#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <pthread.h>

#define MAXSIZE 1024
char buffer_recieve[MAXSIZE];
char buffer_send[MAXSIZE];

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

typedef struct recieve_args
{
	int socketfd;
	int server_len;
	sockaddr_in server_address;
}recieve_args;

void *recieve(void *args);

int main(int argc, char *argv[])
{
    int socketfd;
    int server_len,client_len;
    sockaddr_in server_address;
    sockaddr_in client_address;
    int i,byte;
	//创建socket对象
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_address.sin_family = AF_INET;
	 //主机ip
    server_address.sin_addr.s_addr = inet_addr("10.13.28.135");
    //主机端口
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);

	
	recieve_args args;
	args.server_address = server_address;
	args.server_len = server_len;
	args.socketfd = socketfd;
	
	pthread_t recieveThread;
	int res;
	res = pthread_create(&recieveThread, NULL, recieve, &args);
	if(res != 0)
	{
		perror("fail to create thread");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		printf("send:\n");
		scanf("%s", buffer_send);
		//发送信息给服务器
		if((byte = sendto(socketfd, buffer_send, sizeof(buffer_send), 0,
						(sockaddr *)&server_address,
						(socklen_t)server_len)) == -1)
		{
			perror("send failed");
			exit(EXIT_FAILURE);
		}
	}
    shutdown(socketfd, 2);
    return 0;
}

void *recieve(void *args)
{
	recieve_args *arg = (recieve_args*) args;
	while(1)
	{
		int byte;
		//接收服务器传回的信息
		if((byte = recvfrom(arg->socketfd, &buffer_recieve, sizeof(buffer_recieve), 0,
						//从客户端接受消息
						(sockaddr *)&arg->server_address,
							//存储客户端地址信息
						(socklen_t *)&arg->server_len)) == -1)
		{
			perror("recv failed");
			exit(EXIT_FAILURE);
		}
		printf("\nrecv:%s\n", buffer_recieve);
		fflush(stdout);
	}
}