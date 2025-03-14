cmake_minimum_required(VERSION 4.0.0)

#set the project name 
project(Robot_tasks_management)

# 添加编译选项，确保在 add_executable 之前
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=gbk")

#add the executable
add_executable(Robot_tasks_management main.cpp Robot.cpp task.cpp Robot.h task.h )





