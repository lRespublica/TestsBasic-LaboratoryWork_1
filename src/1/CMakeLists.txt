cmake_minimum_required(VERSION 3.5)

project(1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    coordinates.h
    coordinates.cpp
    mover.h mover.cpp)

add_executable(1 ${PROJECT_SOURCES})
