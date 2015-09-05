/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2015年06月25日 00时05分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (wangweihao), 578867817@qq.com
 *        Company:  xiyoulinuxgroup
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <memory>
#include <vector>

struct sockaddr_in server;
socklen_t len = sizeof(server);

void* func()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("create sockfd error\n");
        exit(1);
    }
    printf("connect...\n");
    int ret = connect(fd, (struct sockaddr*)&server, len);
    if(ret == -1)
    {
        printf("connect error\n");
        exit(1);
    }else{
        printf("connect success\n");
    }
   // char buffer[256];
   // bzero(buffer, 256);
   // strcpy(buffer, "{\"mark\":1,\"account\":\"wangweihao\"}");
   // int t = send(fd, buffer, 256, 0);
   // if(t == -1){
   //     printf("send error\n");
   // }else{
   //     printf("send success\n");
   // }
   // printf("success ..................\n");
   // char buf[256];
   // recv(fd, buf, 256, 0);
   // printf("recv:%s\n", buf);
    sleep(2);
}


int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("argument error\n");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_port = htons((int)atoi(argv[2]));
    server.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server.sin_addr);

    const int k = 50000;
    std::vector<std::shared_ptr<std::thread>> vptr(k);

    for(int i = 0; i < k; i++)
    {
        vptr[i] = std::make_shared<std::thread>(func);
    }
    printf("sleep...");
    sleep(10);

	return EXIT_SUCCESS;
}


