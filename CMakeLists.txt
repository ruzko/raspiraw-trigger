cmake_minimum_required(VERSION 3.0)

project(readpin)

add_executable(readpin main.cpp)

install(TARGETS readpin RUNTIME DESTINATION bin)
