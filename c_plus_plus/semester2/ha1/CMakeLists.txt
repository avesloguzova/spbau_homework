cmake_minimum_required(VERSION 2.8.4)
project(ha1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp linked_ptr.h)
add_executable(ha1 ${SOURCE_FILES})