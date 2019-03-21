#ifndef TCPIP
#define TCPIP

#include <pthread.h>
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


typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct threadArg
{
    int socketFd;
    int server_len;
    sockaddr_in server_address;

}threadArg;

#define MAX_SIZE  1000

extern char messageBuffer[MAX_SIZE];

void* recieveMessage(void* arg);
void connectUDP();


#endif // TCPIP

