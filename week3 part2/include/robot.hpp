#pragma once
#include<string>
#include"task.hpp"
#include<set>
class robot{
    private:
    std::string NAME;
    std::set<task> tasks;
    public:
    robot(std::string name);
    ~robot();
    void addtask(int id, const std::string& description ,int x);
    void executetasks();
    void displaytasks();
    void remove();
};