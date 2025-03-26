cmake_minimum_required(VERSION 4.0.0)

# set the project name 
project(TaskScheduler)

# 添加编译选项，确保在 project 命令之后
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=gbk")

set(SOURCES
    src/main.cpp
    src/Robot.cpp
    src/Task.cpp
    src/TaskScheduler.cpp
)

# add the executable
add_executable(TaskScheduler ${SOURCES})


target_include_directories(TaskScheduler
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# 使用 set_target_properties 设置可执行文件输出路径
set_target_properties(TaskScheduler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)    