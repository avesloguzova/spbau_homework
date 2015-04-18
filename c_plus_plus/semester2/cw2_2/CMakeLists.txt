cmake_minimum_required(VERSION 3.1)
project(cw2_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp)
add_executable(cw2_2 ${SOURCE_FILES} dict.h io_streams.h serialization.h)