#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>
#include "task.hpp"
#include <set>

class Robot{
    private:
        std::string robotname;
        std::set<Task> tasks;
    public:
        Robot() : robotname("") {};
        Robot(std::string name);

        void addTask(int id, std::string description, int importance = 0);
        void executeTasks();
        void displayTasks();
        void deleteTask();
};

#endif