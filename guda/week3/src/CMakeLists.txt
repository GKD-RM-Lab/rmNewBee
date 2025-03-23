cmake_minimum_required(VERSION 4.0.0)

#set the project name 
project(TaskScheduler)

# 添加编译选项，确保在 add_executable 之前
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=gbk")

#add the executable
add_executable(TaskScheduler main.cpp TaskScheduler.cpp Robot.cpp task.cpp Robot.h task.h TaskScheduler.h )
