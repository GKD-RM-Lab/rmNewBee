cmake_minimum_required(VERSION 3.27)

project(project_name CXX C)

#set(CMAKE_C_STANDARD 23)

set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -std=c99")



file(GLOB LIB_SUBDIRS "Lib/*/")

foreach (LIB_SUBDIRS ${LIB_SUBDIRS})

    include_directories(${LIB_SUBDIRS})

endforeach ()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/part2/include)

file(GLOB_RECURSE SOURCES 
"lib/*/*.*" 
"part2/src/*.*"
)

add_executable(SL_Lib ${SOURCES})
