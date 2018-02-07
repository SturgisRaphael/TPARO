cmake_minimum_required(VERSION 3.9)
project(TP3)

set(CMAKE_CXX_STANDARD 11)

add_definitions(
        -std=c99
        -Wall
        -Wextra
)

link_libraries(
        glpk
)

add_executable(TP3
        order.c
        order.h
        main.c
        orderSolver.c orderSolver.h)
