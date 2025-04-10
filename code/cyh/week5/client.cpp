/*客户端*/
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
#include<vector>

using namespace std;

class ctcpclient{
    public:
        int m_clientfd; //客户端socket，-1表示无效, 0表示有效
        string m_ip; //服务端IP/域名
        unsigned short m_port; //通讯端口

        ctcpclient() : m_clientfd(-1){}

//向服务端发起连接请求，成功返回true，失败返回false
        bool connect(const string& in_ip, const unsigned short in_port){
            if(m_clientfd != -1){
               return false;
            }

            m_ip = in_ip;
            m_port = in_port;
            /*创建客户端的socket*/    
            if((m_clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                return false;
            }
            /*向服务器发起连接请求*/
        
            struct sockaddr_in servaddr;  //存放服务端IP和端口的结构体
            memset(&servaddr, 0, sizeof(servaddr)); // 将 servaddr的所有字节初始化为零
            servaddr.sin_family = AF_INET; //IPV4
            servaddr.sin_port = htons(m_port); //指定通信端口， h to ns，h->host, n->network, s->short 
            struct hostent* h;//存放IP的结构体 
            if((h = gethostbyname(m_ip.c_str())) == nullptr){  //字符串转换为结构体
                ::close(m_clientfd);
                m_clientfd = -1;
                return false;
            }       
            memcpy(&servaddr.sin_addr, h->h_addr, h->h_length); //指定IP
           
            if(::connect(m_clientfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){ //发起连接请求
                ::close(m_clientfd);
                m_clientfd = -1;
                return false;
            }
            return true;
        }
//向服务器发送报文，成功返回true，失败返回false
        bool send(const string &buffer, int size){ //buffer不要用const char*,这样兼容性更好
            if(m_clientfd == -1){
                return false;
            }
            if((write(m_clientfd, buffer.data(), size)) <= 0){
                return false;
            }
            return true;
        }
        bool recv(string &buffer, const size_t maxlen){
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
        bool close(){
            if(m_clientfd == -1){
                return false;
            }
            ::close(m_clientfd);
            m_clientfd = -1;
            return true;
        }
        ~ ctcpclient(){
            close();
        }
};


int main(int argc, char *argv[]){
//确保只给了IP和端口两个参数
    if(argc != 3){
        cout << "Using:./client 服务端的IP 服务端的端口\nEample:./client 127.0.0.1 5005\n" << endl;
        return -1;
    } 
    ctcpclient tcpclient;
    if(tcpclient.connect(argv[1],atoi(argv[2])) == false){
        perror("connect");
        return -1;
    }

/*进行通讯*/
    for(int ii = 1; ii < 2; ii++){
        //生成请求报文的内容
        // buffer = "这是第" + to_string(ii + 1) + "条消息, 编号" + to_string(ii + 1) + ". ";
        
        int item_count = 1;
        int item_sum = 1;
        int customerid = 1;
        vector<int> item_quantity;
        item_quantity.push_back(1);

        MessageHeader msgheader;
        msgheader.msgType = ORDER_REQUEST;
        msgheader.msgLength = sizeof(MessageHeader) + sizeof(OrderHeader) + item_count * sizeof(OrderItem);

        OrderHeader orderheader;
        orderheader.customerId = customerid;
        orderheader.itemCount = item_sum;

        vector<OrderItem> items(item_sum);
        items[item_count - 1].foodId = 1;
        items[item_count - 1].quantity = item_quantity[item_count - 1];

        string buffer;
        int offset = 0;

        buffer.resize(msgheader.msgLength );
        memcpy(&buffer[offset], &msgheader, sizeof(MessageHeader));
        offset += sizeof(MessageHeader);
        memcpy(&buffer[offset], &orderheader, sizeof(OrderHeader));
        offset += sizeof(OrderHeader);
      
        
        for (int i = 0; i < orderheader.itemCount; i++) {
            memcpy(&buffer[offset], &items[i], sizeof(OrderItem));
            offset += sizeof(OrderItem);
        }

        for (char c : buffer) {
            printf("%02x ", static_cast<unsigned char>(c));
        }
        printf("\n");
        
        //发送请求报文
            if(tcpclient.send(buffer, msgheader.msgLength) == false){
                perror("send");
                break;
        }
        offset = 0;
        cout << "发送：" << buffer << endl;
        //接收服务端的报文,如果没有发送，recv()函数阻塞
            if((tcpclient.recv(buffer, 1024)) <= 0){
            perror("recv()");
            break;
        }
        cout << "接收：" << buffer << endl;
    }
    close(tcpclient.m_clientfd);
}