#include<iostream>
#include<time.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<thread>
#include"guke.h"
int main(){
    //向working函数传参做初始化
    int max=sizeof(infos)/sizeof(infos[0]);
    for(int i=0;i<max;i++){
        bzero(&infos[i],sizeof(infos[i]));
        infos[i].fd=-1;
    }
    
    //创建线程
    while(1){
        //创建套接字
        struct Sockinfo* pinfo;
        for(int i=0;i<max;i++){
            if(infos[i].fd==-1){
                pinfo=&infos[i];
                break;
            }
        }
        int cfd=socket(AF_INET,SOCK_STREAM,0);
        if(cfd==-1){
            perror("socket");
            return -1;
        } 
        //建立连接
        struct sockaddr_in saddr;
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(30000);
        inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);
        int ret=connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr));
        if(ret==-1){
            perror("connect");
            close(cfd);
            return -1;
        }
        pinfo->fd=cfd;
        std::thread tid(working,pinfo);
        tid.detach();
        return -1;
    }
    return 0;
}
