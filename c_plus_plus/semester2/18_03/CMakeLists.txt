cmake_minimum_required(VERSION 3.1)
project(18_03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vector.h)
add_executable(18_03 ${SOURCE_FILES} vector.h)