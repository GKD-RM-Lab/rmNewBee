#pragma once

#include <string>
#include <vector>
#include "task.h"

class Robot {
private:
    std::string name;
    std::vector<Task> taskQueue;

public:
    Robot(std::string robotName);

    ~Robot();

    void addTask(int id, const std::string& desc);

    void executeTasks();

    void displayTasks();

    void undoTask();
};
