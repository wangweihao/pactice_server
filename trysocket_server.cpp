// =====================================================================================
//
//       Filename:  trysocket.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月03日 19时38分18秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  wangweihao (wangweihao), 578867817@qq.com
//        Company:  none
//
// =====================================================================================

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include <string>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    if(argc < 1)
    {
        std::cout << "argument is not enough" << std::endl;
        exit(1);
    }
    std::string info(argv[1]);
    auto flag = info.find_first_of(':');
    std::string ip = info.substr(0, flag);
    int port = atoi(info.substr(flag+1, info.length()).c_str());

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if(connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cout << "connect failed" << std::endl;
    }
    else
    {
        const char* msg = "abc";
        send(sockfd, msg, strlen(msg), 0);
    }
    close(sockfd);

}
