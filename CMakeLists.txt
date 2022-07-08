cmake_minimum_required(VERSION 3.22)
project(Chess C)

set(CMAKE_C_STANDARD 23)

add_executable(Chess main.c functions.c functions.h)
