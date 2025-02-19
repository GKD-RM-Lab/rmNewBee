#include "taskscheduler.hpp"
#include <iostream>
void TaskScheduler::addRobot(std::string robotname){
    robots[robotname] = Robot(robotname);
}


void TaskScheduler::deleteRobot(std::string robotname){
    robots.erase(robotname);
}

Robot& TaskScheduler::getRobot(std::string robotname){
    std::map<std::string, Robot>::iterator it = robots.find(robotname);
    if (it != robots.end()) {
        return it->second;
    }else{
        std::cout << "没找到" << std::endl;
        return robots["默认"];
    }
}

std::vector<std::string> TaskScheduler::getRobotsName(){
    std::vector<std::string> names;
    for(std::map<std::string, Robot>::iterator it = robots.begin(); it != robots.end(); ++it){
        names.push_back(it->first);
    }
    return names;
}