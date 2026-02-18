cmake_minimum_required(VERSION 3.10)

project(msh VERSION 1.0)

include_directories(include)

add_executable(msh
    src/main.c 
    src/path_utils.c
)
