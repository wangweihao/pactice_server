/*
 * =====================================================================================
 *
 *       Filename:  ucp_server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月27日 12时47分52秒
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
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("argument error\n");
    }
	int port = atoi(argv[2]);
    char *ip = argv[1];

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server.sin_addr);

    int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(udpfd < 0){
        printf("socket udp socketfd error\n");
        exit(-1);
    }
    int ret = bind(udpfd, (struct sockaddr*)&server, sizeof(server));
    if(ret == -1){
        printf("bind error\n");
        exit(-1);
    }
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    char buffer[2048];
    while(1){
        bzero(buffer, 2048);
        int n = recvfrom(udpfd, buffer, 2048, 0, (struct sockaddr*)&client, &len);
        printf("%s\n", buffer);
    }


	return EXIT_SUCCESS;
}


