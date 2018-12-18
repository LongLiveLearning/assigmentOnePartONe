cmake_minimum_required(VERSION 3.13)
project(assigmentOnePartONe)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assigmentOnePartONe
#        main.cpp
        makefile
        Text.cpp
        Text.h
        TextMain.cpp
        TextTester.cpp
        TextTester.h)
