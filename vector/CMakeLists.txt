cmake_minimum_required(VERSION 3.10)   # Minimum CMake version

project(MyProject VERSION 1.0 LANGUAGES CXX)  # Project name and language

set(CMAKE_CXX_STANDARD 17)              # Use C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(my_program vector.cpp)     # Build executable from main.cpp
