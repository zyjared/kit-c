cmake_minimum_required(VERSION 3.30)
project(kit-c VERSION 0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_executable(kit-c src/main.c)
