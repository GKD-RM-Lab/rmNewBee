//客户端
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

using namespace std;

vector<int> menuItems;
mutex coutMutex;
// 读取菜单
void loadMenu(const string& filename) {
    ifstream file(filename);
    for (string line; getline(file, line); ) {
        istringstream iss(line);
        int num;
        if (iss >> num) {  // 自动读取第一个数字（制表符前的内容）
            menuItems.push_back(num);
        }
    }
}

void placeOrder(int customerId) {
    this_thread::sleep_for(chrono::seconds(1 + rand() % 5)); //睡眠1-5秒

    // 生成订单
    vector<int> order;
    int items = 1 + rand() % 3;
    for (int i = 0; i < items; ++i) {
        order.push_back(menuItems[rand() % menuItems.size()]);
    }

    // 创建socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        lock_guard<mutex> lock(coutMutex);
        cerr << "顾客 " << customerId << ": 创建套接字失败" << endl;
        return;
    }
    //关闭端口  
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        shutdown(sock, SHUT_RDWR);
        close(sock);
        return;
    }

    // 设置连接超时（5秒）
    timeval timeout{5, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    // 连接服务器
    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

    if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        lock_guard<mutex> lock(coutMutex);
        cerr << "顾客 " << customerId << ": 连接服务器失败 - " << strerror(errno) << endl;
        shutdown(sock, SHUT_RDWR);
        close(sock);
        return;
    }

    // 准备订单数据
    stringstream orderStream;
    for (size_t i = 0; i < order.size(); ++i) {
        if (i > 0) orderStream << ",";
        orderStream << order[i];
    }
    string orderStr = orderStream.str();

    // 发送订单
    if (send(sock, orderStr.c_str(), orderStr.size(), 0) < 0) {
        lock_guard<mutex> lock(coutMutex);
        cerr << "顾客 " << customerId << ": 发送订单失败" << endl;
        shutdown(sock, SHUT_RDWR);
        close(sock);
        return;
    }

    // 接收响应
    char buffer[1024] = {0};
    int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) {
        lock_guard<mutex> lock(coutMutex);
        cerr << "顾客 " << customerId << ": 未收到服务器响应" << endl;
    } else {
        lock_guard<mutex> lock(coutMutex);
        cout << "顾客 " << customerId << ": 订单 " << orderStr 
             << " " << (buffer[0] == '1' ? "成功" : "失败") << endl;
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
}


int main() {
    srand(time(nullptr));
    loadMenu("foods.txt");

    const int cunstomer_nums = 10;
    vector<thread> customers;

    for (int i = 0; i < cunstomer_nums; ++i) {
        customers.emplace_back(placeOrder, i+1);
    }

    for (auto& t : customers) {
        t.join();
    }

    return 0;
} 