cmake_minimum_required(VERSION 3.12)
project(CAHRR)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_library(CAHRR src/ChassisSystem.cpp src/ChassisSystem.h src/Accumulator.cpp src/Accumulator.h src/Task.cpp src/Task.h src/MockTask.cpp src/MockTask.h src/SwitchTask.cpp src/SwitchTask.h)

add_executable(CAHRR_main main.cpp)
target_link_libraries(CAHRR_main CAHRR)
