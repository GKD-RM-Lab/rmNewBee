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
        std::cerr<< "无法打开文件！" << std::endl;
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
        std::cerr << "无法打开文件。" << std::endl;
    }
}


int  Chef::cooking()
{
    
    init_Socket();
    SOCKET chef = CreateChefSocket();
    //若有客户端请求连接
    SOCKET Custord = accept(chef, NULL, NULL);
    if (INVALID_SOCKET == Custord)
    {
        std::cout << "Custord failed code" << WSAGetLastError();
    }
    //从指定的SOCKET接收消息

    
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
        // 处理订单逻辑
       
    }

    closesocket(Custord);
    closesocket(chef);
    
    



    colse_Socket();

}


bool Chef::CheckStore(int ID)
{
    std::vector<int>mat;
            for (std::vector<std::string>::iterator hand = Menu[ID - 1].materials.begin(); hand != Menu[ID - 1].materials.end(); hand++)//根据找到的对应的菜从菜所需的第一个材料开始从仓库里面拿
            {
                
                for (int material = 0; material <= Store.size()-1; material++)//根据所需材料从仓库里面找
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
    //af :地址协议  type 传输协议类型 （套接字，数据报）    protocl 使用具体的某个传输协议
    SOCKET chef = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (chef == INVALID_SOCKET)//如果启动失败
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

    //为socket绑定IP和端口
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
