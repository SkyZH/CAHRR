cmake_minimum_required(VERSION 3.12)
project(CAHRR)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
add_subdirectory(mock)

add_library(CAHRR src/AvgAccumulator.cpp src/AvgAccumulator.h src/Task.cpp src/Task.h src/PIDAccumulator.cpp src/PIDAccumulator.h src/RampAccumulator.cpp src/RampAccumulator.h src/RotateAccumulator.cpp src/RotateAccumulator.h src/SwitchTask.cpp src/SwitchTask.h src/Task.cpp src/Task.h)

add_executable(CAHRR_main main.cpp)
target_link_libraries(CAHRR_main CAHRR)
