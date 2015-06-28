/*
 * =====================================================================================
 *
 *       Filename:  udp_server.c
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2015年06月27日 13时09分28秒
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
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
        printf("argument error\n");
        exit(1);
    }
    char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server.sin_addr);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        printf("socket create error\n");
        exit(1);
    }

    char buffer[3000];
    int j = 0;
    for(j = 0; j < 1; j++){
        bzero(buffer, 3000);
        int i = 0;
        for(i = 0; i < 3000; i++){
            buffer[i] = 'c';
        }
        //scanf("%s", buffer);
        int n = sendto(sockfd, buffer, 3000, 0, (struct sockaddr*)&server, sizeof(server));
        if(n <= 0){
            printf("send error\n");
            exit(1);
        }else{
            printf("send success:%s\n", buffer);
        }
    }

	return EXIT_SUCCESS;
}


