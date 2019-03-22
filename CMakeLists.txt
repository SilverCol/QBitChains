cmake_minimum_required(VERSION 3.12)
project(vaja_II_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(run src/main.cpp src/experiments.hpp)
target_link_libraries(run gflags pthread)
