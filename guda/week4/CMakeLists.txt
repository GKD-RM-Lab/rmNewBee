cmake_minimum_required(VERSION 4.0.0)

project(Task_Management_Class)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/task_manager.cpp
    src/task.cpp
)

# add the executable
add_executable(Task_Management_Class ${SOURCES})

target_include_directories(Task_Management_Class
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# 使用 set_target_properties 设置可执行文件输出路径
set_target_properties(Task_Management_Class PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)    