#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include "task.h"

class Robot {
private:
    std::string name;         
    Task taskQueue[100];  
    int taskCount;            

public:
    Robot(std::string robotName); 
    ~Robot(); 
    void addTask(int id, std::string desc);
    void executeTasks(); 
    void displayTasks(); 
};

#endif // ROBOT_H
