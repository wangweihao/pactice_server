/*
 * =====================================================================================
 *
 *       Filename:  udp_client_connect.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年07月02日 23时27分40秒
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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
        printf("argument error\n");
        exit(1);
    }

    char *ip = argv[1];
    struct sockaddr_in server;
    struct sockaddr_in client;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, ip, &server.sin_addr);
    
    client.sin_family = AF_INET;
    client.sin_port = htons(8000);
    //inet_pton(AF_INET, "192.168.23.3", &client.sin_addr);
    inet_pton(AF_INET, INADDR_ANY, &client.sin_addr);


    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0){
        printf("create socket error\n");
        exit(1);
    }

    int bret = bind(fd, (struct sockaddr*)&client, sizeof(client));
    if(bret == -1){
        printf("bind error\n");
        exit(1);
    }
    int cret = connect(fd, (struct sockaddr*)&server, sizeof(server));
    if(cret == -1){
        printf("connect error\n");
        printf("%d\n", cret);
        strerror(errno);
        printf("%d\n", errno);
        exit(1);
    }else{
        printf("connect success!\n");
    }
    char buf[1000] = "hello world";
    int n = sendto(fd, buf, 1000, 0, (struct sockaddr*)&server, sizeof(server));
    //int n = write(fd, buf, 1000);
    //int n = sendto(fd, buf, 1000, 0, NULL, 0);
    //int n = send(fd, buf, 1000, 0);
    if(n <= 0){
        printf("send error\n");
    }

	return EXIT_SUCCESS;
}


