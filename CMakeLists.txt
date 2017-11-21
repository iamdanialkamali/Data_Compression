cmake_minimum_required(VERSION 3.8)
project(DS_Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector.h amir.cpp amir.h)
add_executable(DS_Project ${SOURCE_FILES})