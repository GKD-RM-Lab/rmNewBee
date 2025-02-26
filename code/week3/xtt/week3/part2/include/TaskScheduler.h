#pragma once
#include<map>
#include<vector>
#include<string>
#include"robot.h"
using namespace std;

class TaskScheduler
{
public:
	map<string, Robot>RobotList;
	vector<string>RobotNameList;
	void AddRobot(const Robot &robot);
	void DelRobot(string RobotName);
	void InquireRobot(string RobotName);
	void ShowNameList();
};