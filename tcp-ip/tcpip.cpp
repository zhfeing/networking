#include "tcpip.h"
char messageBuffer[MAX_SIZE];

void *recieveMessage(void *arg)
{
    threadArg* args = (threadArg*)arg;
    int byte;
    while(1)
    {
        /*//接收服务器传回的信息
        if((byte = recvfrom(args->socketFd, &messageBuffer, sizeof(messageBuffer), 0,
                        (sockaddr *)&args->server_address,
                            (socklen_t *)&args->server_len)) == -1)
        {
            perror("recvprom");
            exit(EXIT_FAILURE);
        }
        flag_getMessage = 1;
        printf("%s\n", messageBuffer);*/
        char send[10] = "hellow";
    int byte;
    if((byte = sendto(args->socketFd, &send, sizeof(send), 0,
                    (sockaddr *)&args->server_address,
                    (socklen_t)args->server_len)) == -1)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}
void connectUDP()
{
    int socketfd;
    int server_len, client_len;
    sockaddr_in server_address;
    sockaddr_in client_address;

    //创建socket对象
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_address.sin_family = AF_INET;
    //主机ip
    server_address.sin_addr.s_addr = inet_addr("10.25.144.50");
    //主机端口
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);

    //begin Thread
    int res;
    pthread_t a_thread;
    void *thread_result;
    threadArg arg;
    arg.server_address = server_address;
    arg.server_len = server_len;
    arg.socketFd = socketfd;
    //send hellow packeg
    char send[10] = "hellow";
    int byte;
    if((byte = sendto(socketfd, &send, sizeof(send), 0,
                    (sockaddr *)&server_address,
                    (socklen_t)server_len)) == -1)
    {
        perror("send");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, NULL, recieveMessage, (void *)&arg);
    if (res != 0)
    {
        perror("Thread creation failed!");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(a_thread, &thread_result);
    printf("%s\n", (char*) thread_result);
    if (res != 0)
    {
        perror("Thread join failed!/n");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        //发送信息给服务器
    }
    shutdown(socketfd, 2);
}
