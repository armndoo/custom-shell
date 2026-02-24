cmake_minimum_required(VERSION 3.10)
project(msh)

set(CMAKE_C_STANDARD 99)


add_executable(msh
    src/main.c 
    src/parser.c 
    src/builtins.c
    src/path_utils.c
    src/execute.c
    src/utils.c
)
target_include_directories(msh PUBLIC include)
