#include"Customer.h"
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
bool Customer::init_Socket()
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		std::cout << "WSAStartup failed code" << WSAGetLastError();
		return false;
	}
	return true;
}

bool Customer::colse_Socket()
{
	if (WSACleanup() != 0)
	{
		std::cout << "WSACleanup failed code" << WSAGetLastError();
		return false;
	}
	return true;


}


SOCKET Customer::CreateCustomerSocket()
{
	//af :地址协议  type 传输协议类型 （套接字，数据报）    protocl 使用具体的某个传输协议
	SOCKET customer =socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (customer == INVALID_SOCKET)//如果启动失败
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
		closesocket(customer);
		return INVALID_SOCKET;
	}
	if (INVALID_SOCKET == connect(customer, (struct sockaddr*)&addr, sizeof(addr)))
	{
		std::cout << "connect1 failed code" << WSAGetLastError();
		return false;

	}


	listen(customer, 10);

	return customer;
}


void Customer::Order()
{
	init_Socket();

	SOCKET customer = CreateCustomerSocket();
	int order = LookMenu();
	std::string orderStr = std::to_string(order);
	send(customer, orderStr.c_str(), orderStr.length(), 0);
	std::cout << order << std::endl;
	char buffer[1024];
	int bytesReceived = recv(customer, buffer, sizeof(buffer) - 1, 0); 
	if (bytesReceived > 0) {
		buffer[bytesReceived] = '\0';
		std::cout << "Server received: " << buffer << std::endl;
	}
	closesocket(customer);
	colse_Socket();
}


int Customer::LookMenu()
{
	srand(std::time(0));
	while (1)
	{
		int food = std::rand() % 7;
		if (food >= 1 && food <= 6)
		{
			return food;
		}
	}
}
