#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
struct Sockinfo{
    struct sockaddr_in addr;
    int fd;
};
int count=0;
//判断是否充足
void read(int linenum){//剩余数量固定在第九列之后 
    FILE*fp=fopen("库存信息.txt","r");
        if(fp==NULL){
            perror("无法打开文件");
            return;
        }
    char line[100];
    int currentline=1;
    while(fgets(line,sizeof(line),fp)!=NULL){
        if(currentline==linenum){
            if(line[8]==0){
                printf("库存不足");
                log(linenum);
                count++;
            }
            else{
                printf("库存充足");
            }
            break;
        }
        currentline++;
    }
    fclose(fp);
}
//判断食物信息对应哪种
int *judge(int linenum){
     FILE*fp=fopen("食物信息.txt","r");
     if(fp==NULL){
        perror("无法打开文件");
        return NULL;
     }
     int *food=(int *)malloc(sizeof(int)*20);
        if(food==NULL){
        perror("内存分配失败");
        fclose(fp);
        return NULL;
     }
     int x=0;
     while(x<20){
        food[x]=-1;
        x++;
     }
    char line[100];
    int currentline=1;
    while(fgets(line,sizeof(line),fp)!=NULL){
        if(currentline==linenum+1){//需要的食材在下一行
            int i=0,j=0;
            while(1){
                if(line[i]!='o'){
                    food[j]=line[i];
                    j++;
                    i=i+2;
                }
                else{
                    break;
                }
            }
        }
        currentline++;
    }
    fclose(fp);
    return food; 
}
//用去某种食材
void write(int linenum){
    FILE*fp=fopen("库存信息.txt","r+");
    if(fp==NULL){
        perror("无法打开文件");
        return ;
    }
    char line[100];
    int currentline=0;
    while(fgets(line,sizeof(line),fp)!=NULL){
        if(currentline==linenum){
            fseek(fp,9,SEEK_SET);
            int a=9;
            while(1){        //判断是几位数
                if(line[a]==' ') break;
                else a++;
            }
            int b=0,c=0;
            while(1){
                if(a!=9){
                    b+=(line[a]-'0')*pow(10,c);
                    c++;
                    a--;
                }
                else break;
            }
            b--;
            fseek(fp,9,SEEK_SET);
            fprintf(fp,"%d",b);
            break;
        }
        currentline++;
    }
    fclose(fp);
}
//写log文件
void log(int a){
    FILE*fp=fopen("菜单.log","a");
        if(fp==NULL){
            perror("无法打开文件");
            return;
        }
    fprintf(fp,"第%d行食物库存不足",a);
    fclose(fp);
    printf("写入成功");
}
void* working(void* arg)
{
    struct Sockinfo* pinfo=(struct Sockinfo*)arg;
    char ip[32];
    pthread_mutex_t houchu_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&houchu_lock);
    while(1){
        int *buff=(int *)malloc(sizeof(int));
        if(buff==NULL){
            perror("内存分配失败");
            pthread_mutex_unlock(&houchu_lock);
        close(pinfo->fd);
        pinfo->fd=-1;
        return NULL;
        }
        int len=recv(pinfo->fd,buff,sizeof(buff),0);
        if(len>0){
            int file=*buff;
            int *foods=judge(file);
            if(foods==NULL){
                free(buff);
                pthread_mutex_unlock(&houchu_lock);
                close(pinfo->fd);
                pinfo->fd=-1;
                return NULL;
            }
            int y=0;
            while(1){
                //判断是否充足
                if(foods[y]!=-1) {
                    read(foods[y]);
                    y++;
                }
                else break;
            //不充足
            if(count!=0){
                 while(1){
                    int y=0;
                    if(foods[y]!=-1) {
                        log(foods[y]);
                        y++;
                    }
                    else break;
            }
                free(foods);
            }
            //充足
            else{
                int a=1;
                send(pinfo->fd,&a,sizeof(int),0);
                int *foods=judge(file);
                if(foods==NULL){
                    free(buff);
                    pthread_mutex_unlock(&houchu_lock);
                    close(pinfo->fd);
                    pinfo->fd=-1;
                    return NULL;
                }
                int y=0;
                while(1){
                    if(foods[y]!=-1) {
                        write(foods[y]);
                        y++;
                    }
                    else break;
            }
                free(foods);
        }
        }
        }
        else if(len==0){
            printf("客户端已经断开连接");
            break;
        }
        else{
            perror("recv");
            break;
        }
        free(buff);
    }
    pthread_mutex_unlock(&houchu_lock);
    close(pinfo->fd);
    pinfo->fd=-1;
    return NULL;
}
