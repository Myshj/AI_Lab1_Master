cmake_minimum_required(VERSION 3.6)
project(AI_Lab1_Master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILE ParticleSwarmOptimization.h
    main.cpp)

add_executable(AI_Lab1_Master main.cpp)