cmake_minimum_required(VERSION 2.8)

project(wserver)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(wserver ${PROJECT_SOURCE_DIR}/src/opt_parser.h)
add_executable(wserver ${PROJECT_SOURCE_DIR}/src/opt_parser.cpp)

add_executable(wserver ${PROJECT_SOURCE_DIR}/src/main.cpp)
