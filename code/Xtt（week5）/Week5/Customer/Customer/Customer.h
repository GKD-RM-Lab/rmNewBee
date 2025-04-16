#pragma once
#include<thread>
#include<vector>

#include<iostream>

#include<winsock2.h>

#include<random>
#include<string>
class Customer
{
public:	
	std::thread customer1;
	std::thread customer2;
	std::thread customer3;
	void Order();
	int LookMenu();
	SOCKET CreateCustomerSocket();
	bool init_Socket();
	bool colse_Socket();
private:
	

};