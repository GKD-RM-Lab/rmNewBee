#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
struct Sockinfo{
    struct sockaddr_in addr;
    int fd;
};
struct Sockinfo infos[512];
void* working(void* arg){
    struct Sockinfo* pinfo=(struct Sockinfo*)arg;
    srand((unsigned int)time(NULL));
    int order=rand()%7;
    send(pinfo->fd,(const void*)&order,sizeof(order),0);
    printf("顾客已发送");
    int *buff = (int *)malloc(sizeof(int));
    int len = recv(pinfo->fd, buff, sizeof(int), 0);
    if(len>0){
        printf("顾客已接受");
    }
    else{
        perror("recv");
    }
    sleep(rand());        
    close(pinfo->fd);
    return NULL;
}