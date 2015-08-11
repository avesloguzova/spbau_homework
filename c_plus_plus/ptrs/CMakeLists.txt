cmake_minimum_required(VERSION 2.8.4)
project(ptrs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp singleton.h singleton.cpp)
add_executable(ptrs ${SOURCE_FILES})