#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP

#include "robot.hpp"
#include <map>
#include <string>
#include <vector>

class TaskScheduler{
    private:
        std::map<std::string, Robot> robots;
        Robot defaultRobot;
    public:
        TaskScheduler() : defaultRobot("默认") {
            robots["默认"] = defaultRobot;
        }
        void addRobot(std::string robotname);
        void deleteRobot(std::string robotname);
        Robot &getRobot(std::string robotname);
        std::vector<std::string> getRobotsName();
        
};



#endif