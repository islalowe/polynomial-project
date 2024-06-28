cmake_minimum_required(VERSION 3.22)
project(polynomial_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(polynomial_project
        polynomial.cpp
        polynomial.h
        unit-test.cpp)
