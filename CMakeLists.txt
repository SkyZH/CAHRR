cmake_minimum_required(VERSION 3.12)
project(CAHRR)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(test)
add_subdirectory(mock)

add_library(CAHRR src/AvgAccumulator.cpp src/AvgAccumulator.h src/Task.cpp src/Task.h src/PIDAccumulator.cpp src/PIDAccumulator.h src/RampAccumulator.cpp src/RampAccumulator.h src/RotateAccumulator.cpp src/RotateAccumulator.h src/SwitchTask.cpp src/SwitchTask.h src/Task.cpp src/Task.h src/AutoSwitchTask.cpp src/AutoSwitchTask.h src/ConditionSwitchTask.cpp src/ConditionSwitchTask.h src/TriggerSwitchTask.cpp src/TriggerSwitchTask.h src/TimedTask.cpp src/TimedTask.h src/SequentialTask.cpp src/SequentialTask.h src/ParallelTask.cpp src/ParallelTask.h src/UltrasonicSystem.h)

add_executable(CAHRR_main main.cpp)
target_link_libraries(CAHRR_main CAHRR)
