cmake_minimum_required(VERSION 3.1)
project(hw2_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(hw2_2 ${SOURCE_FILES} lazy_string.h)