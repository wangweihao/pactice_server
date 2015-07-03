/*
 * =====================================================================================
 *
 *       Filename:  send_file_server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年07月04日 01时26分54秒
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
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
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
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server.sin_addr);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("create socket error\n");
        exit(1);
    }
    int b_ret = bind(fd, (struct sockaddr*)&server, sizeof(server));
    if(b_ret == -1){
        printf("bind error\n");
        exit(1);
    }
    int l_ret = listen(fd, 64);
    if(l_ret == -1){
        printf("listen error\n");
        exit(1);
    }
    socklen_t len = sizeof(server);
    int sockfd = accept(fd, (struct sockaddr*)&server, &len);
    if(sockfd == -1){
        printf("accept error\n");
        exit(1);
    }else{
        printf("connect success\n");
    }
    char name[128];
    char buffer[2048];
    bzero(name, 128);
    bzero(buffer, 2048);
    int n = recv(sockfd, name, 2048, 0);
    if(n <= 0){
        printf("recv error\n");
        exit(1);
    }
    printf("name:%s\n", name);
    int w_fd = open(name, O_WRONLY | O_CREAT, 777);
    if(w_fd == -1){
        printf("open file error\n");
        exit(1);
    }
    off_t pos = lseek(w_fd, 0, SEEK_CUR);
    if(pos < 0){
        printf("obtain file pointer error\n");
        exit(1);
    }
    while(1){
        bzero(buffer, 2048);
        int n = recv(sockfd, buffer, 2048, 0);
        if(n < 0){
            printf("recv error\n");
            exit(1);
        }else if(n == 0){
            break;
        }
        ssize_t s_t = write(w_fd, buffer, n);
        if(s_t < 0){
            printf("write error\n");
            exit(1);
        }
    }
    printf("recv file success!!!\n");


	return EXIT_SUCCESS;
}


