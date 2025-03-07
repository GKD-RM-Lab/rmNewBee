cmake_minimum_required(VERSION 3.10)

project(TaskManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(TaskManager main.cpp)
set(CMAKE_BUILD_TYPE Debug)

