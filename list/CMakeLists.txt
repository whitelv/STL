cmake_minimum_required(VERSION 3.10)   # Minimum CMake version

project(MyProject VERSION 1.0 LANGUAGES CXX)  # Project name and language

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_program list.cpp)     # Build executable from main.cpp
