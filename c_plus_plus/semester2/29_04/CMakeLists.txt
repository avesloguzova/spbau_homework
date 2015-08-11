cmake_minimum_required(VERSION 3.1)
project(29_04)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(29_04 ${SOURCE_FILES} data_monitor.h)