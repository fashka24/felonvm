cmake_minimum_required(VERSION 3.30)
project(felonvm C)

set(CMAKE_C_STANDARD 23)

add_executable(felonvm main.c
        src/felonvm.c)
