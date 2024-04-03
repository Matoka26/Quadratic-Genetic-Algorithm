cmake_minimum_required(VERSION 3.27)
project(Algoritmi_genetici)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Algoritmi_genetici
        main.cpp
        main.h
        Generation.h
        Interval.h
        Equation.h
        NullStream.h)
