cmake_minimum_required(VERSION 3.10)

project(geometry_module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(geometry_module STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gm_primitives.cpp
)

target_include_directories(geometry_module
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)