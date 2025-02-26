#include"TaskScheduler1.h"
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

void TaskScheduler::AddRobot(const Robot &robot)
{
	RobotList.insert(pair<string, Robot>(robot.RobotName, robot));
	RobotNameList.push_back(string(robot.RobotName));
}
void TaskScheduler::DelRobot(string RobotName)
{
	auto result = RobotList.erase(RobotName);
	if (result == 0) {
		std::cout << "Not found " << RobotName << " fail to delete。" << std::endl;
	}
	else {
		cout << "Successfully delete the name of " << RobotName <<endl;
		auto it = find(RobotNameList.begin(), RobotNameList.end(), RobotName);
		RobotNameList.erase(it);
	}
	
}
void TaskScheduler::InquireRobot(string RobotName)
{
	map<string, Robot>::iterator pos = RobotList.find(RobotName);
	if (pos != RobotList.end())
	{
		pos->second.ShowTask();
	}
	else
	{
		cout << "Not found" << endl;
	}
}
void TaskScheduler::ShowNameList()
{
	cout << "Name of existing robots:" << endl;
	for (vector<string>::iterator it = RobotNameList.begin(); it != RobotNameList.end(); it++)
	{
		cout << (*it) << endl;
    }
}