//��������
/*ά���˵��Ϳ��
���ܶ����������
�ۼ���沢ͬ����¼���ļ��л��߷���ʧ��
��¼��ϸ��־(ʱ�������Ʒ���ƣ��Ƿ���ɣ�ʳ������ʣ������)
ʹ�ö��̲߳����������ͻ��ĵ㵥����*/

#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <fstream>
#include <WinSock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
    
struct Food{
    int id;//��Ų�Ʒ���
    string name;//��Ų�Ʒ����
    vector<string>ingredients;//��Ų�ƷҪ�õ�ʳ��
};

vector<Food>meun;
unordered_map<string,int>ingreds;//�ù�ϣ��ķ�����ӳ���棬�������Ƿ���ʳ�ģ���Ϊ�����޹���������unordered_map����������
mutex log_m,kc;//�Կ�����־д��Ҫ���м���

//��ȡ����Щ��Ʒ
void load_menu(const string& Filename){
    //ifstream��ֻ���ļ����࣬ofstream��ֻд�ļ����࣬fstream���ܵ��ļ�������(��д�����Խ���)
    ifstream file(Filename);//���ļ�
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
        getline(buffer,food.name,' ');//��ȡ��Ʒ�����ƣ������ո��ֹͣ����

        string ingrediens;
        // while (buffer>>ingrediens){
        //     food.ingredients.push_back(ingrediens);
        // }
        while(getline(buffer,ingrediens,' ')){
            food.ingredients.push_back(ingrediens);
        }
        meun.push_back(food);//��ȫ����һ����Ʒ�Ժ󣬰�����ŵ�meun����
        // cout<<food.name;
        // for(auto &i:food.ingredients){
        //     std::cout<<i<<"ooooo"<<" "<<food.ingredients.size();
        // }
        // cout<<"wwwwwwwwwwwwwwwwwwwwwwww"<<endl;
        
    }
    
}

//��ȡ��棬��ŵ�unordered_map��
void load_ingredient(const string& Filename){
    ifstream file(Filename);
    if(!file.is_open()){
        cerr<<"The food_inventory file failed to open.."<<endl;
        return;
    }
    string buf;
    int quantity;
    while(file>>buf>>quantity){//�Զ����տո�ָ�
        ingreds[buf]=quantity;
        //cout<<buf<<" "<<quantity<<endl;��ȡ�ļ���ȷ
        //cout<<ingreds[buf]<<endl;
    }
}

//����д����־�ĺ���������־����׷��ģʽ
void write_log(const string& log_msg){
    lock_guard<mutex>lock(log_m);//��д����־�����������������߳�ͬʱ������־��ɻ���
    //cout<<log_msg;//����log_msg��Ŀ���һֱ����һ������
    ofstream log_file("Food.log",ios::app/*|ios::binary*/);//��׷�ӷ�ʽ���ļ�
    if(log_file.is_open()){
        //��ȡ��ǰʱ��(ʱ���)
        auto now=chrono::system_clock::now();
        auto now_time=chrono::system_clock::to_time_t(now);
        //����ʱ���ʽ��ʼ��,����������д��log�ļ�֮��
        log_file<<put_time(localtime(&now_time),"\n%Y-%m-%d %H:%M:%S")<<"|"<<log_msg<<"\n";
    }
}

//���ж�������
string order_del(const string& order){
    //����Ĵ���˼·��:ֻ�����㶩�������в�Ʒ�����������Ż����order finish��Ϊ��������������
    //ֻҪ�����������һ���޷���ɣ�Ҳ�ж�Ϊfailed
    unordered_map<string,int>test=ingreds;
    cout<<"The order function has been entered."<<endl;
    //istringstream���ַ���ת��Ϊ�ɶ�ȡ����
    istringstream buffer(order);
    vector<int>food_ids;
    int id;
    while(buffer>>id){
        food_ids.push_back(id);
    }
    //�Զ������������������������߳�ͬʱ������ɿ���¼ʧ��
    lock_guard<mutex>lock(kc);
    //ostringstream֧�ֽ��������͵����ݸ�ʽ��Ϊ�ַ���
    ostringstream log_msg,respond;//��log_msg��respendǿ��ת��Ϊ������ַ���
    log_msg.str("");//ȷ��Ϊ��
    log_msg<<"Task:";//��ʽд�룬�ȶ��ƴ���ַ������㣬������д���������
    //��Ϊ��־�ļ����������������������Ӣ����

    vector<string>ordered_food;//����ͻ������еĲ�Ʒ����
    vector<bool>is_finish(food_ids.size(),true);

    bool all_order=true;
    
    for(size_t i=0;i<food_ids.size();i++){
        int id=food_ids[i];
        //���ȼ���Ʒid�Ƿ���Ч
        if(id<0||id>meun.size())
        {
            all_order=false;
            break;
        }

        Food& index_dish=meun[id-1];//��ȡ��Ӧ���ֵĲ�Ʒ,��Ϊmeun�Ǵ��±�0��ʼ�洢��Ʒ��
        ordered_food.push_back(index_dish.name);

        //log_msg<<" "<<index_dish.name;
        //������Ƿ��㹻
        //����ѭ����������index_dish�е�ԭ���ϣ���ͨ����ϣ��鿴�Ƿ���ʣ��ʳ��
        for(auto &inv:index_dish.ingredients){
            //ֻҪ��һ���治�����Ƕ������˵�ǰ��Ʒ
            cout<<inv<<endl;
            if(test[inv]<=0){
                //cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                all_order=false;
                is_finish[i]=false;
                break;
            }
            test[inv]--;
        }  
    }
    respond<<(all_order==true?1:-1)<<" ";
    //cout<<respond.str()<<endl;
    //ֻ������id�������Ҳ� Ʒ�������������������order
    //Ҫ������ʳ�Ķ�����ʣ�࣬�Ǿͽ���۳�������˵Ľ׶�
    if(all_order==true){
        ingreds=test;
    }else{
        test=ingreds;
    }

    log_msg<<"[";
    for(size_t i=0;i<ordered_food.size();i++){
        if(i!=0) log_msg<<" ";
        log_msg<<ordered_food[i]<<" "<<(is_finish[i]?" dish Finished":"dish Failed")<<endl<<"\t\t\t\t\t\t\t";
    }
    log_msg<<"]"<<(all_order?" order Finished ":" order Failed ")<<"[";
    for(auto it=ingreds.begin();it!=ingreds.end();it++){
        //cout<<it.first<<" "<<it.second;
        log_msg<<it->first<<" "<<it->second<<"; ";
    }
    log_msg<<"]";
    write_log(log_msg.str());//��ȡostringstream���е����ݣ�ת��Ϊ�ַ�����������־�ļ���д��
    return respond.str();
}

//�̺߳���������ͻ�����
DWORD WINAPI client_deal(LPVOID lpParam){
    SOCKET client_socket=*(SOCKET*)lpParam;
    char buffer[1024]={0};

    //���ܿͻ��˴���Ķ�������
    int recevied=recv(client_socket,buffer,sizeof(buffer),0);
    if(recevied<=0){
        closesocket(client_socket);
        return 1;
    }

    //�����������лظ���Ӧ
    string order(buffer,recevied);
    string respendse=order_del(order);
    //cout<<respendse<<endl;
    send(client_socket,respendse.c_str(),respendse.size(),0);

    closesocket(client_socket);
    delete (SOCKET*)lpParam;//�ͷ��ڴ�
    return 0;
}

int main(){
    load_menu("menu.txt");
    load_ingredient("food_inventory.txt");
    //cout<<meun[0].name;
    //��ʼ�������
    WSADATA net;
    //Windowsר�������ʼ��
    if(WSAStartup(MAKEWORD(2,2),&net)!=0){
        cerr<<"...Failed to initialize the network..."<<endl;
        return -1;
    }

    //����socket
    SOCKET server_socket=socket(AF_INET,SOCK_STREAM,0);//Э�������д0����ϵͳ�����׽���(�ڶ�������)�����Զ�ѡ��Ĭ��Э��
    if(server_socket==INVALID_SOCKET){
        cerr<<"...Failed to create socket..."<<endl;
        WSACleanup();
        return -2;
    }

    //��ip�Ͷ˿�
    sockaddr_in server_addr;//sockaddr_in�����ڴ洢ipv4��ַ�Ͷ˿ںŵĽṹ��
    server_addr.sin_family=AF_INET;//��ַ��
    server_addr.sin_port=htons(8080);//�󶨶˿�8080
    server_addr.sin_addr.s_addr = INADDR_ANY;//�������ж˿�
    if(bind(server_socket,(sockaddr*)&server_addr,sizeof(server_addr))==SOCKET_ERROR){
        cerr<<"Failed to bind IP and port."<<endl;
        WSACleanup();
        return -3;
    }
    //��ʼ����
    if(listen(server_socket,SOMAXCONN)==SOCKET_ERROR){
        cerr<<"Bugging failed."<<endl;
        WSACleanup();
        return -4;
    }

    cout<<"The server side is connected to port 8080..."<<endl;    
    //ѭ���������ǽ��ܿͻ��˵����ӣ�����ÿ����һ���߳�������һ���ͻ��Ķ���
    while (1)
    {
        sockaddr_in client_addr;//�洢�ͻ��˵�ipV4��ַ
        int client_addr_len=sizeof(client_addr);
        SOCKET client_socket = accept(server_socket,(sockaddr*)&client_addr,&client_addr_len);
        /*
        //
        SOCKET* client_socket_ptr = new SOCKET(client_socket);
        HANDLE work_thread = CreateThread(NULL, 0, client_deal, client_socket_ptr, 0, NULL);*/
        if(client_socket==INVALID_SOCKET){
            cerr<<"Error connecting to client."<<WSAGetLastError()<<endl;
            continue;
        }
        cout<<"The client is connected"<<endl;
        //�����߳�,����ʹ����windows API����
        HANDLE work_thread=CreateThread(NULL,0,client_deal,&client_socket,0,NULL);
        if(work_thread==NULL){
            cerr<<"The thread creation failed."<<endl;
            continue;//�����ȴ���һ������
        }
        else{
            CloseHandle(work_thread);//�ͷ��߳̾��(�̼߳�������)
        }
    }
    //������Դ
    closesocket(server_socket);
    WSACleanup();
    return 0;
}

