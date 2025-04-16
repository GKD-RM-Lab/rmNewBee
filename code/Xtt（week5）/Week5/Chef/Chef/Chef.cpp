#include"Chef.h"

#include <fstream>
#include <sstream>
#pragma comment(lib,"ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

void Chef::getMenu()
{
	std::ifstream file("C:/Users/xtt/source/repos/Chef/Chef/resource/Menu.txt");
    if (!file.is_open()) {
        std::cerr<< "�޷����ļ���" << std::endl;
        return ;
    }
    std::string line;
    Food dish;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> dish.num;
        iss >> dish.name;
        std::string material;
        while (iss >> material) {
            dish.materials.push_back(material);
        }
        Menu.push_back(dish);
        dish.materials.clear();
    }
    file.close();
}

void Chef::FillStore()
{
    std::ifstream file("C:/Users/xtt/source/repos/Chef/Chef/resource/Resource.txt");
    

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int quantity;
            while (iss >> name >> quantity) {
                Store.emplace_back(name, quantity);
            }
        }
        file.close();

    }

}
void Chef::WriteLog(int FoodID,int Finish)
{
    time_t current_time;
    struct tm current_tm;
    time(&current_time);

    
    if (localtime_s(&current_tm, &current_time) != 0) {
        std::cerr << "Failed to get local time." << std::endl;
        return ;
    }
    std::ofstream outFile("C:/Users/xtt/source/repos/Chef/Chef/resource/Log.txt", std::ios::app);

    if (outFile.is_open()) {
        outFile << current_tm.tm_hour<<":";
        outFile << current_tm.tm_min<<":";
        outFile << current_tm.tm_sec<<" ";
        outFile << Menu[FoodID -1].name<<" ";
        if (Finish == 1)
        {
            outFile << "complete ";
        }
        else if(Finish == -1)
        {
            outFile << "uncompleted ";
        }
        outFile << "[";
        for (std::vector<std::string>::iterator hand = Menu[FoodID - 1].materials.begin(); hand != Menu[FoodID - 1].materials.end(); hand++)
        {
            for (std::vector<std::pair<std::string, int>>::iterator material = Store.begin(); material != Store.end(); material++)
            {
                
                if ((*hand) == (*material).first)
                {
                    
                    outFile << (*material).first<<" ";
                    outFile << (*material).second<<" ";
                }

            }

        }
        outFile << "]" << std::endl;
        
        outFile.close();
       
    }
    else {
        std::cerr << "�޷����ļ���" << std::endl;
    }
}


int  Chef::cooking()
{
    
    init_Socket();
    SOCKET chef = CreateChefSocket();
    //���пͻ�����������
    SOCKET Custord = accept(chef, NULL, NULL);
    if (INVALID_SOCKET == Custord)
    {
        std::cout << "Custord failed code" << WSAGetLastError();
    }
    //��ָ����SOCKET������Ϣ

    
    char buffer[1024];
    int bytesReceived = recv(Custord, buffer, sizeof(buffer)-1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        int order = std::stoi(buffer);
        Orders.push_back(order);
  
         while(!Orders.empty())
         {
             int num = Orders.front();
            
             if (CheckStore(num))
             {
                 
                 std::string response = "1";
                 WriteLog(num, 1);
                 send(Custord, response.c_str(), response.length(), 0);
             }
             else
             {
                 std::string response = "-1";
                 WriteLog(num, -1);
                 send(Custord, response.c_str(), response.length(), 0);
             }
             Orders.pop_front();
             

         }
        // �������߼�
       
    }

    closesocket(Custord);
    closesocket(chef);
    
    



    colse_Socket();

}


bool Chef::CheckStore(int ID)
{
    std::vector<int>mat;
            for (std::vector<std::string>::iterator hand = Menu[ID - 1].materials.begin(); hand != Menu[ID - 1].materials.end(); hand++)//�����ҵ��Ķ�Ӧ�Ĳ˴Ӳ�����ĵ�һ�����Ͽ�ʼ�Ӳֿ�������
            {
                
                for (int material = 0; material <= Store.size()-1; material++)//����������ϴӲֿ�������
                {
                    
                    if ((*hand) == Store[material].first)
                    {
                        
                        if (Store[material].second!=0)
                        {
                            
                            mat.push_back(material);
                            
                        }   
                        else
                        {
                           return false;
                        }
                    }

                }
            }
            
            for (int i = 0; i <= mat.size() - 1; i++)
            {
                Store[mat[i]].second--;
            }
            

            return true;
}

SOCKET Chef::CreateChefSocket()
{
    //af :��ַЭ��  type ����Э������ ���׽��֣����ݱ���    protocl ʹ�þ����ĳ������Э��
    SOCKET chef = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (chef == INVALID_SOCKET)//�������ʧ��
    {
        std::cout << "socket failed code" << WSAGetLastError();
        return INVALID_SOCKET;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    const char ipAddress[] = "127.0.0.1";
    if (InetPtonA(AF_INET, ipAddress, &addr.sin_addr) != 1) {
        std::cout << "InetPtonA failed code: " << WSAGetLastError() << std::endl;
        closesocket(chef);
        return INVALID_SOCKET;
    }

    //Ϊsocket��IP�Ͷ˿�
    if (SOCKET_ERROR == bind(chef, (sockaddr*)&addr, sizeof(addr)))
    {
        std::cout << "bind failed code" << WSAGetLastError();
        return false;
    }

    listen(chef, 10);

    return chef;
}

bool Chef::init_Socket()
{
    WSADATA wsadata;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
    {
        std::cout << "WSAStartup failed code" << WSAGetLastError();
        return false;
    }
    return true;
}

bool Chef::colse_Socket()
{
    if (WSACleanup() != 0)
    {
        std::cout << "WSACleanup failed code" << WSAGetLastError();
        return false;
    }
    return true;
}
