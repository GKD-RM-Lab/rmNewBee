#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
#include"guke.h"
int main(){
    std::cout<<"1";
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
        inet_pton(AF_INET,"192.168.43.5",&saddr.sin_addr.s_addr);
        int ret=connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr));
        if(ret==-1){
            perror("connect");
            close(cfd);
            return -1;
        }
        pinfo->fd=cfd;
        working(pinfo);
        pthread_t tid;
        int creat=pthread_create(&tid,NULL,working,pinfo);
        if(creat!=0){
        perror("pthread_create");
        return -1;
    }
        pthread_detach(tid);
        return 0;
    }
    
}
