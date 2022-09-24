cmake_minimum_required(VERSION 3.5)

project(2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    coordinates.h
    coordinates.cpp
    mover.h mover.cpp)

add_executable(2 ${PROJECT_SOURCES})
