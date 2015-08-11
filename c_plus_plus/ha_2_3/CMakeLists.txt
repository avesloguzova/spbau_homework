cmake_minimum_required(VERSION 3.2)
project(ha_2_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ha_2_3 ${SOURCE_FILES})