#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include<thread>
#include<string>
#include<math.h>
#include<mutex>
#include<atomic>
#include<fstream>
struct Sockinfo{
    struct sockaddr_in addr;
    int fd;
};
std::atomic<int> count(0);
//判断是否充足
void read(int linenum){//剩余数量固定在第九列之后 
    std::ifstream ifs("库存信息.txt");
        if(!ifs.is_open()){
            perror("无法打开文件");
            return;
        }
    std::string line;
    int currentline=1;
    while(std::getline(ifs,line)){
        if(currentline==linenum){
            if(line[8]==0){
                std::cout<<"库存不足";
                log(linenum);
                count++;
            }
            else{
                std::cout<<"库存充足";
            }
            break;
        }
        currentline++;
    }
    ifs.close();
}
//判断食物信息对应哪种
int *judge(int linenum){
     std::ifstream ifs("食物信息.txt");
     if(!ifs.is_open()){
            perror("无法打开文件");
            return NULL;
        }
     int *food=(int *)malloc(sizeof(int)*100);
        if(food==NULL){
        perror("内存分配失败");
        ifs.close();
        return NULL;
     }
     int x=0;
     while(x<100){
        food[x]=-1;
        x++;
     }
    std::string line;
    int currentline=1;
    while(std::getline(ifs,line)){
        if(currentline==linenum+1){//需要的食材在下一行
            int i=0,j=0;
            while(1){
                if(line[i]!='o'&&i<line.size()){
                    if(j<100){
                    food[j]=static_cast<int>(line[i]);
                    }
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
    ifs.close();
    return food; 
}
//用去某种食材
void write(int linenum){
    std::fstream fs("库存信息.txt",std::ios::in|std::ios::out);
    if(!fs.is_open()){
            perror("无法打开文件");
            return;
        }
    std::string line;
    int currentline=0;
    while(std::getline(fs,line)){
        if(currentline==linenum){
            fs.seekg(9,std::ios::cur);
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
            fs.seekg(9,std::ios::cur);
            fs<<b;
            break;
        }
        currentline++;
    }
    fs.close();
}
//写log文件
void log(int a){
    std::ofstream ofs("菜单.log",std::ios::app);
        if(!ofs.is_open()){
            perror("无法打开文件");
            return;
        }
    ofs<<"第"<<a<<"行食物不足";
    ofs.close();
    printf("写入成功");
}
std::mutex houchu_lock;
void* working(void* arg)
{
    struct Sockinfo* pinfo=(struct Sockinfo*)arg;
    char ip[32];
    while(1){
        houchu_lock.lock();
        int *buff=(int *)malloc(sizeof(int));
        if(buff==NULL){
            perror("内存分配失败");
            houchu_lock.unlock();
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
                houchu_lock.unlock();
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
                    houchu_lock.unlock();
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
    houchu_lock.unlock();
    close(pinfo->fd);
    pinfo->fd=-1;
    return NULL;
}
