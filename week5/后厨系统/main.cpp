#include<iostream>
#include<arpa/inet.h>
#include<thread>
#include<string.h>
#include<math.h>
#include<mutex>
#include"houchu.h"
int main(){
    //创建套接字
    int fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        perror("socket");
        return -1;
    }  
    //绑定服务器
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(30000);
    saddr.sin_addr.s_addr=INADDR_ANY;
    int ret=bind(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("bind");
        close(fd);
        return -1;
    }
    //设置监听
    ret=listen(fd,128);
    if(ret==-1){
        perror("listen");
        return -1;
    }
    struct Sockinfo infos[512];
    //准备working参数
    int max=sizeof(infos)/sizeof(infos[0]);
    for(int i=0;i<max;i++){
        bzero(&infos[i],sizeof(infos[i]));
        infos[i].fd=-1;
    }
    //设置接受函数 创造线程
    socklen_t addrlen=sizeof(struct sockaddr_in);
    while(1){
        struct Sockinfo* pinfo;
        for(int i=0;i<max;i++){
            if(infos[i].fd==-1){
                pinfo=&infos[i];
                break;
            }
        }
        int cfd=accept(fd,(struct sockaddr*)&pinfo->addr,&addrlen);
        std::cout<<"收到客户端连接！";  // 在 accept() 成功后添加
        pinfo->fd=cfd;
    std::thread tid(working,pinfo);
    tid.detach();
    }
    close(fd);
    return 0;
    
}