cmake_minimum_required(VERSION 3.9)
project(TP3)

set(CMAKE_CXX_STANDARD 11)

add_executable(TP3
        order.c
        order.h
        main.c
        Makefile orderSolver.c orderSolver.h)

ADD_DEFINITIONS(
        -std=c99
        -Wall
        -Wextra
        -lglpk
)