#include "task_scheduler.h"

#include <iostream>

void TaskScheduler::addRobot(const std::string &name) {
    if(robot_list.count(name)) {
        std::cerr << "has: " << name << std::endl;
        return;
    }
    robot_list[name] = new Robot(name);
}

void TaskScheduler::deleteRobot(const std::string &name) {
    if(!robot_list.count(name)) {
        std::cerr << "no robot named " << name << std::endl;
        return;
    }
    delete robot_list[name];
    robot_list.erase(name);
}

Robot* TaskScheduler::getRobot(const std::string &name) {
    if(!robot_list.count(name)) {
        throw std::runtime_error("no robot named " + name);
    }
    return robot_list[name];
}

std::vector<std::string> TaskScheduler::getRobotNameList() {
    std::vector<std::string> res;
    for(auto [key, val] : robot_list) {
        res.push_back(key);
    }
    return res;
}