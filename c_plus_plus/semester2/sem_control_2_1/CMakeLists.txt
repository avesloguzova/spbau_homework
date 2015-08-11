cmake_minimum_required(VERSION 2.8.4)
project(sem_control_2_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp task_queue.h)
add_executable(sem_control_2_1 ${SOURCE_FILES})