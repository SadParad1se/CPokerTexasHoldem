cmake_minimum_required(VERSION 3.16)
project(CPoker)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c helpers.c helpers.h game.c game.h)

add_executable(CPoker ${SOURCE_FILES})