cmake_minimum_required(VERSION 4.3)
project(2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2 main.cpp
        Rectangle/Rectangle.cpp
        Rectangle/Rectangle.h
        Car/Car.cpp
        Car/Car.h
        Truck/Truck.cpp
        Truck/Truck.h
        Stack/Stack.cpp
        Stack/Stack.h
        Pr1/Pr1.cpp
        Pr1/Pr1.h
        Pr2/Pr2.cpp
        Pr2/Pr2.h
)
