#pragma once
#include<map>
#include<string>
#include<vector>
#include"robot.hpp"
class scheduler{
    private:
    std::map<std::string, robot *> Robots;
    public:
    void addrobot(const std::string& name);
    void deletrobot(const std::string& name);
    robot* getRobot(const std::string &name);
    void gainRobot();
};