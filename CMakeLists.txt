cmake_minimum_required(VERSION 3.10)

project(geometry_module LANGUAGES CXX)

add_library(geometry_module STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vectors.cpp
)

target_include_directories(geometry_module
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/geometry_module.hpp
)