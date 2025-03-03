#pragma once
#include<string>
#include"task.hpp"
#include<vector>
class robot{
    private:
    std::string NAME;
    std::vector<task> tasks;
    public:
    robot(std::string name);
    ~robot();
    void addtask(int id, const std::string& description);
    void executetasks();
    void displaytasks();
    void remove();
};