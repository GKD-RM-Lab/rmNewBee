#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>
#include "task.hpp"

class Robot{
    private:
        std::string Robotname;
        std::vector<Task> tasks;
    public:
        Robot(std::string name);
        ~Robot();
        void addTask(int id, std::string description);
        void executeTasks();
        void displayTasks();
};

#endif