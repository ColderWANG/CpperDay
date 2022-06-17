#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>

#define SERV_PORT 9527

void sys_err(const char *str){
    perror(str);
    exit(1);   //0表示正常退出，1表示异常退出
}


int main(int argc, char **argv){
    int sfd, cfd, f;
    struct sockaddr_in serv_addr, clit_addr;                //服务端网络地址结构
    socklen_t clit_addrlen;
    char buf[BUFSIZ], clit_ip[1024];

    //参数初始化
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    clit_addrlen = sizeof(clit_addr);

    sfd = socket(AF_INET, SOCK_STREAM, 0);   //创建套接字
    if(sfd == -1) sys_err("socket error \r\n");

    f = bind(sfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));  //绑定服务端socket
    if(f == -1) sys_err("bind error \r\n");

    listen(sfd, 128);       //设置服务端监听客户端的数量上限
    cfd = accept(sfd, (struct sockaddr*)&clit_addr, &clit_addrlen); //监听客户端
    if(cfd == -1)sys_err("accept error");
    printf("client IP: %s, port: %d \n",
            inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, clit_ip, sizeof(clit_ip)),
            ntohs(clit_addr.sin_port));
    while(1){
        int ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        for(int i = 0; i < ret; ++i){
            buf[i] = toupper(buf[i]);
        }
        write(cfd, buf, ret);
    }
    close(sfd);
    close(cfd);
}