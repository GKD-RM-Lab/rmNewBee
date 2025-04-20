//�ͻ���
/*
���ڽ��ܿͻ���Ŀ
���ͻ��������ݸ�server�������˽����ж�
ÿ���ͻ����ö������߳�
*/
#define WIN32_LEAN_AND_MEAN //����windowͷ�ļ���ͻ
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

struct Food{
    int id;//��Ų�Ʒ���
    string name;//��Ų�Ʒ����
    vector<string>ingredients;//��Ų�ƷҪ�õ�ʳ��
};

vector<Food>menu;

void load_menu(const string& filename){
    //ifstream��ֻ���ļ����࣬ofstream��ֻд�ļ����࣬fstream���ܵ��ļ�������(��д�����Խ���)
    ifstream file(filename);//���ļ�
    if(!file.is_open()){
        cerr<<"The menu file failed to open."<<endl;
        return;
    }
    string buf;//����һ����������һ��һ�ж�ȡ�ļ������Ϣ
    while (getline(file,buf))
    {
        istringstream buffer(buf);//��һ������ת��Ϊ�ַ�������ʹ����������û�����һ������>>�����ж�ȡ
        Food food;
        buffer>>food.id;
        buffer>>ws;//�����հ��ַ�
        getline(buffer,food.name,'\t');//��ȡ��Ʒ�����ƣ�����tab����ֹͣ����

        string ingrediens;
        while (buffer>>ingrediens){
            food.ingredients.push_back(ingrediens);
        }
        menu.push_back(food);//��ȫ����һ����Ʒ�Ժ󣬰�����ŵ�meun����
    }
}

//�����������ӵĺ���
void connect_server(int cus_id,const vector<int>&ithems){
    //��ʼ�������
    WSADATA net;
    //Windowsר�������ʼ��
    if(WSAStartup(MAKEWORD(2,2),&net)!=0){
        cerr<<"...Failed to initialize the network...."<<endl;
        return;
    }

    //����socket
    SOCKET client_socket=socket(AF_INET,SOCK_STREAM,0);//Э�������д0����ϵͳ�����׽���(�ڶ�������)�����Զ�ѡ��Ĭ��Э��
    if(client_socket==INVALID_SOCKET){
        cerr<<"...Failed to create socket...."<<endl;
        WSACleanup();
        return;
    }

    //���ӷ�����
    sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    //inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(connect(client_socket,(sockaddr*)&server_addr,sizeof(server_addr))==SOCKET_ERROR){
        cerr<<"An error occurred on the linked server side."<<endl;
        //cerr<<"...Incorrect link to the server..."<<endl;
        closesocket(client_socket);
        WSACleanup();
        return;
    }

    //���Ͷ���
    ostringstream order;
    for(int item:ithems){
        order<<item<<" ";
    }
    send(client_socket,order.str().c_str(),order.str().size(),0);

    //������Ӧ
    char buffer[1024]={0};
    int respond_server=recv(client_socket,buffer,sizeof(buffer),0);
    if(respond_server==0){
        cerr<<"The server side is not responding."<<WSAGetLastError()<<endl;
        
        //cerr<<"...Serverdid not respond..."<<endl;
    }
    else{
        istringstream respondse(buffer);//�����յ���������bufferת��Ϊ�ַ��������Ҵ�����respondse��
        int result;
        bool all_deal=true;
        while(respondse>>result){
            if(result==-1){
                all_deal=false;
            }
        }
        cout<<"client:"<<cus_id<<(all_deal?"   Order fulfilled":"Out-of-stock failure")<<endl;
        //cout<<"client:"<<cus_id<<(all_deal?"order completion":"Lack of inventory")<<endl;
    }
    closesocket(client_socket);
    WSACleanup();
}

int main(){
    //��ȡ�ļ�����Ҫ�ǻ�ȡ��Ʒ����
    load_menu("menu.txt");
    int dish_num=menu.size();
    if(dish_num<=0){
        cout<<"The current menu is empty"<<endl;
        //cout<<"The current menu is empty."<<endl;
        return 0;
    }
    int num_cus;
    cout<<"Please enter the number of customers:";
    //cout<<"Pls enter the number of customer:";
    cin>>num_cus;
    vector<thread>customers;
    //�����������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<>item_dish(1,static_cast<int>(menu.size()));//���ݲ˵���С��������������Ʒ
    //���ｫ�˿Ϳ��Ե�Ĳ�Ʒ�޶�Ϊһ���ˣ�Ҫ��Ҫ�����͸�һ����һ��������ķ�Χֵ����
    uniform_int_distribution<>count_dish(1,1);//ÿ���˿�����ܵ�Ͳ˵�������һ���Ĳ�Ʒ
    //********** */

    //�����̴߳���ÿ���˿͵Ķ�����ÿ���̴߳���һ���˿�
    for(int i=0;i<num_cus;++i){
        customers.emplace_back([i,&item_dish,&count_dish,&gen](){
            this_thread::sleep_for(chrono::milliseconds(100*i));
            int item_count=count_dish(gen);
            vector<int>items;
            for(int j=0;j<item_count;++j){
                items.push_back(item_dish(gen));
            }
            connect_server(i+1,items);
        });
    }
    for(auto& th:customers){
        th.join();
    }

    return 0;
}