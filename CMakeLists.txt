cmake_minimum_required(VERSION 3.12)
project(vaja_II_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(run src/main.cpp src/experiments.hpp src/Propagator.cpp src/Propagator.h src/Suzuki4.cpp src/Suzuki4.h src/Suzuki2.cpp src/Suzuki2.h src/Trotter.cpp src/Trotter.h src/QState.cpp src/QState.h)
target_link_libraries(run gflags pthread)
