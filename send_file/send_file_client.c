/*
 * =====================================================================================
 *
 *       Filename:  send_file_client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年07月04日 00时42分05秒
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
#include <sys/sendfile.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
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
    int con_ret = connect(fd, (struct sockaddr*)&server, sizeof(server));
    if(con_ret == -1){
        printf("connect error\n");
        exit(1);
    }
    char *name = argv[3];
    int r_fd = open(name, O_RDONLY);
    if(r_fd == -1){
        printf("open file error\n");
        exit(1);
    }
    struct stat st;
    int size = stat(name, &st);
    if(size < 0){
        printf("file stat error\n");
        exit(1);
    }
    printf("file size:%d\n", st.st_size);
    off_t pos = lseek(r_fd, 0, SEEK_SET);
    if(pos < 0){
        printf("obtain fileP error\n");
        exit(1);
    }
    char *cname = "newfile";
    int sn = send(fd, cname, sizeof(argv[3]), 0);
    int n = sendfile(fd, r_fd, &pos, st.st_size);
    if(n == -1){
        printf("send file error\n");
        exit(1);
    }

	return EXIT_SUCCESS;
}


