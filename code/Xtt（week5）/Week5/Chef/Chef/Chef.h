#pragma once
#include<vector>
#include"Food.h"
#include<iostream>
#include<thread>
#include<ctime>
#include<time.h>
#include<winsock2.h>
#include<random>
#include<string>
#include<atomic>
#include<deque>
class Chef
{
public:

	
	void getMenu();
	void FillStore();
	int cooking();
	bool CheckStore(int ID);
	SOCKET CreateChefSocket();
	bool init_Socket();
	bool colse_Socket();
	void WriteLog(int FoodID, int Finish);

public:
	std::deque<int>Orders;
	std::vector<Food>Menu;
	std::vector<std::pair<std::string, int>> Store;
	
}; 