/*服务端*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"order.h"

using namespace std;

class ctcpserver{
    public:
        int m_listenfd;
        int m_clientfd;
        string clientip;
        unsigned short m_port;

        ctcpserver() : m_listenfd(-1), m_clientfd(-1){}
//服务端初始化
        bool init_server(const unsigned short in_port){
            /*创建服务端socket*/
            if((m_listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                return false;
            }
            m_port = in_port;
           /*把服务端用于通信的IP和端口绑定到socket上*/
            struct sockaddr_in servaddr;  //存放服务端IP和端口的结构体
            memset(&servaddr, 0, sizeof(servaddr)); // 将 servaddr的所有字节初始化为零
            servaddr.sin_family = AF_INET; //IPV4
            servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //服务端任意的IP都可以通讯
            servaddr.sin_port = htons(m_port); //指定通信端口
           /*socket设置为可监听状态*/
            if(bind(m_listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
                close(m_listenfd);
                m_clientfd = -1;
                return false;
            }
            if(listen(m_listenfd, 5) != 0){
                close(m_listenfd);
                m_listenfd = -1;
                return false;
            }
            return true;
        }
//受理客户端的连接请求
        bool accept(){
            struct sockaddr_in caddr;
            socklen_t addrlen = sizeof(caddr);
            m_clientfd = ::accept(m_listenfd, (struct sockaddr *)& caddr, &addrlen);
            if(m_clientfd == -1){
                close(m_listenfd);
               return false;
            }      
            return true;
        }
 //发送报文
        bool send(const string& buffer){
            if(m_clientfd == -1){
                return false;
            }
            if((write(m_clientfd, buffer.data(), buffer.size())) <= 0){
               return false;
            }
            return true;
        }
//接受报文
        bool recv(string& buffer, const size_t maxlen){
            buffer.clear();
            buffer.resize(maxlen);
            int readn = read(m_clientfd, &buffer[0], buffer.size()); //buffer.data()返回的是const的，这里我们可能直接修改buffer，因此不用那种
            if(readn <= 0){ //-1失败，0连接断开
                buffer.clear();
                return false;
            }
            buffer.resize(readn);
            return true;
        }
//关闭socket
        bool close_listen(){
            if(m_listenfd == -1){
                return false;
            }
            ::close(m_listenfd);
            m_listenfd = -1;
            return true;
        }
        bool close_client(){
            if(m_clientfd == -1){
                return false;
            }
            ::close(m_clientfd);
            m_clientfd = -1;
            return true;
        }
//解析报文
        bool parseMessage(string& buffer){
            MessageHeader msgheader;
            memcpy(&msgheader,buffer.data(), sizeof(MessageHeader));
            if(msgheader.msgType != ORDER_REQUEST){
                cout <<"msgheader"<< endl;
                return false;
            }
            OrderHeader orderheader;
            memcpy(&orderheader, buffer.data(), sizeof(OrderHeader));
            int offset = sizeof(MessageHeader) + sizeof(OrderHeader);
            
            OrderItem items[orderheader.itemCount];
            for (int i = 0; i < orderheader.itemCount; i++) {
                memcpy(&items[i], buffer.data() + offset, sizeof(OrderItem));
                offset += sizeof(OrderItem);
            }
            cout << "foodID" << items->foodId << endl;
            return true;
        }
        ~ ctcpserver(){
            close_listen();
            close_client();
        }

    
};

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "端口错误" << endl;
        return -1;
    }

    ctcpserver tcpserver;
    if(tcpserver.init_server(atoi(argv[1])) == false){
        perror("init_server()");
        return -1;
    }

    if(tcpserver.accept() == false){
        perror("accept()");
        return -1;
    }
    cout << "客户端已连接。\n";

    string buffer;
    while (true)
    {

        
        if((tcpserver.recv(buffer, 1024)) == false){
            perror("recv()");
            return -1;
        }

        if (buffer.size() < sizeof(MessageHeader)) {
            cerr << "buffer" << endl;
            return -1;
        }
        cout << "已接收" << endl;


        if(tcpserver.parseMessage(buffer) == false){
            cerr << "parseMessage()" << endl;
            return -1;
        }

        cout << "已解析" << endl;

    //    MessageHeader msgheader;
    //    memcpy(&msgheader,buffer.data(), sizeof(MessageHeader));
    //    if(msgheader.msgType != ORDER_REQUEST){
    //        cout <<"msgheader"<< endl;
    //        return -1;
    //    }
    //    OrderHeader orderheader;
    //    memcpy(&orderheader, buffer.data(), sizeof(OrderHeader));
    //    int offset = sizeof(MessageHeader) + sizeof(OrderHeader);
       
    //    OrderItem items[orderheader.itemCount];
    //    for (int i = 0; i < orderheader.itemCount; i++) {
    //        memcpy(&items[i], buffer.data() + offset, sizeof(OrderItem));
    //        offset += sizeof(OrderItem);
    //    }


        buffer = "ok";

            if((tcpserver.send(buffer)) == false){
                perror("send()");
                return -1;
            }
            cout << "发送：" << buffer << endl;
        }
        
    }

