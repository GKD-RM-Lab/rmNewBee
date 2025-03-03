#include"TaskScheduler.hpp"
#include<iostream>
#include<vector>
void scheduler::addrobot(const std::string& name){
    robot *ROBOT=new robot(name); 
    Robots.insert({name,ROBOT});
}
void scheduler::deletrobot(const std::string& name){
    Robots.erase(name);
}
robot* scheduler::getRobot(const std::string& name){
    auto it = Robots.find(name);
    return it->second;
}
void scheduler::gainRobot(){
    std::vector<std::string> names;
    for(auto it : Robots)
    names.emplace_back(it.first);
    for(int i=0;i<names.size();i++){
        std::cout<<names[i]<<std::endl;
    }

}

