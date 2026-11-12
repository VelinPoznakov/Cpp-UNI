cmake_minimum_required(VERSION 4.3)
project(4)

set(CMAKE_CXX_STANDARD 20)

add_executable(4 main.cpp
        Vehicle/Vehicle.cpp
        Vehicle/Vehicle.h
        Car/Car.cpp
        Car/Car.h
        Truck/Truck.cpp
        Truck/Truck.h
        Item/Item.cpp
        Item/Item.h
        Movie/Movie.cpp
        Movie/Movie.h
        Game/Game.cpp
        Game/Game.h
        Music/Music.cpp
        Music/Music.h
)
