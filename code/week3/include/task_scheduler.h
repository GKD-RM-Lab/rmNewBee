#pragma once

#include <map>
#include <vector>
#include "robot.h"
#include "task.h"

class TaskScheduler {
private:
    std::map<std::string, Robot *> robot_list;
public:
    void addRobot(const std::string &name);

    void deleteRobot(const std::string &name);

    Robot* getRobot(const std::string &name);

    std::vector<std::string> getRobotNameList();
};