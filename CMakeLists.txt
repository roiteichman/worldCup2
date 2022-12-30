cmake_minimum_required(VERSION 3.21)
project(worldCup2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(worldCup2
        AVLTree.h
        main.cpp
        Player.cpp
        Player.h
        DoubleHashing.h
        dynamicArray.h
        Team.cpp
        Team.h
        wet2util.h
        worldcup23a2.cpp
        worldcup23a2.h)
