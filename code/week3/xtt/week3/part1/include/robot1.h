#include"task1.h"
#include<string>
#include<vector>
using namespace std;
class Robot
{
public:
    Robot();
    Robot(string name);
    void AddTask(int ID, string Describe);
    void ExeTask();
    void ShowTask();
    void CanTask();
    ~Robot();
    string RobotName;
    vector<task>TaskList;
};
