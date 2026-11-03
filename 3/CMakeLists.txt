cmake_minimum_required(VERSION 4.3)
project(3)

set(CMAKE_CXX_STANDARD 20)

add_executable(3 main.cpp
        Point/Point.cpp
        Point/Point.h
        Array/Array.cpp
        Array/Array.h
        Stack/Stack.cpp
        Stack/Stack.h
        Queue/Queue.cpp
        Queue/Queue.h
        Student/Student.cpp
        Student/Student.h
        StudentList/StudentList.cpp
        StudentList/StudentList.h
)
