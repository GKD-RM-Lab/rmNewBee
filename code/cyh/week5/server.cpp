//服务器端
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <ctime>
#include <algorithm>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

// 食材信息
struct FoodItem {
    int id;
    string name;
    vector<string> ingredients;
};  

// 库存信息
map<int, FoodItem> foods;
map<string, int> inventory;
mutex inventory_mutex;
mutex log_mutex;

//读取食材信息的分割函数
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s); //将s转换为字符串流，以便按分隔符分割
    while (getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}
//读取食材信息
void loadFoods(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, '\t');
        if (parts.size() < 3) continue;

        FoodItem item;
        item.id = stoi(parts[0]);
        item.name = parts[1];
        // 分割食材部分
        vector<string> ingredients = split(parts[2], ' ');
        for (const string& ing : ingredients) {
            if (!ing.empty()) {
                item.ingredients.push_back(ing);
            }
        }
        foods[item.id] = item;
    }
    file.close();
}

//读取库存信息(不用加锁，因为只在开头调用一次)
void loadInventory(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        // 跳过空行
        if (line.empty()){
            continue;
        } 
        
        stringstream ss(line);
        string name;
        int quantity;
        
        if (ss >> name >> quantity) {
            inventory[name] = quantity;
            cout << "Loaded inventory: " << name << " = " << inventory[name] << endl;
        } else {
            cerr << "inventory.txt格式错误: " << line << endl;
        }
    }
    file.close();
}

string getCurrentTime() {
    time_t now = time(0); //获取当前时间
    tm *ltm = localtime(&now);  //转换为本地时间
    char buf[20];
    strftime(buf, sizeof(buf), "%H-%M-%S", ltm);
    return string(buf);
}

//记录订单信息
void logOrder(const vector<int>& order, bool success, const map<string, int>& updates) {
    lock_guard<mutex> lock(log_mutex);
    ofstream logfile("kitchen.log", ios::app); //append模式打开日志文件
    
    // 记录时间
    logfile << getCurrentTime() << " "; 
    
    // 记录订单内容
    for (size_t i = 0; i < order.size(); ++i) {
        if (i > 0) logfile << ",";
        logfile << order[i];
    }
    
    // 记录成功状态
    logfile << " " << (success ? "1" : "0") << " [";
    
    // 记录食材状态
    bool end = false;
    for (const auto& [ing, qty] : updates) {
        if (end){
             logfile << "; ";
        }
        logfile << ing << " " << qty;
        end = true;
    }
    logfile << "]" << endl;
    
    logfile.close();
} 


bool processOrder(const vector<int>& order, map<string, int>& updates) {
    lock_guard<mutex> lock(inventory_mutex);
    bool allSuccess = true;
    bool hasInvalidID = false;

    // 首先将整个inventory复制到updates
    updates = inventory;

    map<string, int> totalDemand;
    // 检查ID有效性并收集食材需求
    for (int id : order) {
        if (foods.find(id) == foods.end()) {
            hasInvalidID = true; 
            continue;
        }
        const FoodItem& item = foods[id];
        for (const string& ing : item.ingredients) {
            totalDemand[ing]++;
        }
    }

    // 存在无效ID则订单失败
    if (hasInvalidID) {
        allSuccess = false;
    } else {
        // 检查库存是否足够
        for (const auto& [ing, demand] : totalDemand) {
            if (inventory.find(ing) == inventory.end() || inventory[ing] < demand) {
                allSuccess = false;
                break;
            }
        }
    }

    // 如果订单可以处理，更新库存和updates中对应的值
    if (allSuccess) {
        // 扣减库存并更新updates
        for (const auto& [ing, demand] : totalDemand) {
            inventory[ing] -= demand;
            updates[ing] = inventory[ing]; // 更新对应的值
        }
    }
    // 如果订单不能处理，updates仍然包含完整的inventory快照

    return allSuccess;
}
//处理客户端请求
void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        close(clientSocket);
        return;
    }

    vector<int> order;
    stringstream ss(buffer);
    string item;
    // 解析客户端请求
    while (getline(ss, item, ',')) {
       order.push_back(stoi(item));
    } 

    map<string, int> updates;
    bool success = processOrder(order, updates);
    
    string response = success ? "1" : "-1";
    send(clientSocket, response.c_str(), response.size(), 0);
    //生成日志
    logOrder(order, success, updates);
    close(clientSocket);
}

void server_init(int serverFd) {
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(serverFd, (struct sockaddr*)&address, sizeof(address));
    listen(serverFd, 5);
    cout << "8080端口启动成功" << endl;
}

void server_loop(int serverFd) {
    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);
        int clientSocket = accept(serverFd, (struct sockaddr*)&clientAddr, &addrLen);
        
        if (clientSocket < 0) {
            cerr << "接受失败" << endl;
            continue;
        }
        thread(handleClient, clientSocket).detach(); //分离线程处理客户端请求
    }}


int main() { 
    loadFoods("foods.txt");
    loadInventory("inventory.txt");
    // 创建服务器套接字
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    server_init(serverFd);
    
    server_loop(serverFd);
    return 0;
}
