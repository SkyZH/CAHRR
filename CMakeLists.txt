cmake_minimum_required(VERSION 3.12)
project(CHARR)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_library(CHARR src/ChassisSystem.cpp src/ChassisSystem.h src/Accumulator.cpp src/Accumulator.h)

add_executable(CHARR_main main.cpp)
target_link_libraries(CHARR_main CHARR)
