cmake_minimum_required(VERSION 3.2)
project(contest_150615_aum)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES taskA.cpp)
add_executable(taskA ${SOURCE_FILES})

set(SOURCE_FILES taskE.cpp)
add_executable(taskC ${SOURCE_FILES})

set(SOURCE_FILES taskD.cpp)
add_executable(taskD ${SOURCE_FILES})

set(SOURCE_FILES taskC.cpp)
add_executable(taskE ${SOURCE_FILES})

set(SOURCE_FILES taskF.cpp)
add_executable(taskF ${SOURCE_FILES})