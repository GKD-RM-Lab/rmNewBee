cmake_minimum_required(VERSION 4.0.0)

#set the project name 
project(Robot_tasks_management)

#add the executable
add_executable(Robot_tasks_management main.cpp Robot.cpp task.cpp Robot.h task.h )

set(CMAKE_CXX_STANDARD 11)


