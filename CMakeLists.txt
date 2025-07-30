cmake_minimum_required(VERSION 3.25)

project(squeeze)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(squeeze_executable 
    src/main.cpp
    src/infinite_precision_proportion.cpp
    )

target_compile_options(squeeze_executable PRIVATE -Wall -Wextra)