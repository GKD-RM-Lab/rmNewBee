#include <iostream>
#include <map>
#include "robot.h"
#include "task.h"
#include "task_scheduler.h"

using namespace std;

int main() {
    TaskScheduler task_scheduler;
    string command;
    std::vector<std::string> valid_command = {"add_robot", "add_task", "undo", "exec", "delete", "query", "list"};

    while (true) {
        cout << "Please enter the command (add_robot/add_task/undo/exec/delete/query/list/exit): ";
        cin >> command;

        if (command == "exit") {
            break;
        } else if(command == "list") {
            auto list = task_scheduler.getRobotNameList();
            std::cout << "name list:" << std::endl;
            for(const auto &name_ : list) {
                std::cout << name_ << std::endl;
            }
            continue;
        } else if(std::find(valid_command.begin(), valid_command.end(), command) == valid_command.end()){
            std::cout << "invalid command" << std::endl;
            continue;
        }
        std::string name;
        std::cin >> name;
        if (command == "add_robot") {
            task_scheduler.addRobot(name);
        } else if(command == "add_task") {
            int id;
            string desc;
            cin >> id >> desc;
            task_scheduler.getRobot(name)->addTask(id, desc);
        } else if (command == "undo") {
            task_scheduler.getRobot(name)->undoTask();
        } else if (command == "exec") {
            task_scheduler.getRobot(name)->executeTasks();
        } else if (command == "delete") {
            task_scheduler.deleteRobot(name);
        } else {
            task_scheduler.getRobot(name)->displayTasks();
        }
    }

    return 0;
}
