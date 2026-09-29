cmake_minimum_required(VERSION 4.3)
project(1)

set(CMAKE_CXX_STANDARD 20)

add_executable(1 main.cpp
        Time/Time.cpp
        Time/Time.h
        Employee/Employee.cpp
        Employee/Employee.h
        Line/Line.cpp
        Line/Line.h
)
