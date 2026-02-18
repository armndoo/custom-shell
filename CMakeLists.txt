cmake_minimum_required(VERSION 3.10)

project(custom_shell VERSION 1.0)

include_directories(include)

add_executable(custom_shell
    src/main.c 
    src/path_utils.c
)
