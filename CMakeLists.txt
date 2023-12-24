cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(heap)
set(CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES main.cpp)
set(INCLUDE_DIRS ./)

add_executable(heap ${SOURCES})

target_include_directories(heap PUBLIC ${INCLUDE_DIRS})
target_compile_options(heap PRIVATE -g)
