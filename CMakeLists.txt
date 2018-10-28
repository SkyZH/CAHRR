cmake_minimum_required(VERSION 3.12)
project(CAHRR)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_library(CAHRR mock/MockChassisSystem.cpp mock/MockChassisSystem.h src/AvgAccumulator.cpp src/AvgAccumulator.h src/Task.cpp src/Task.h mock/MockTask.cpp mock/MockTask.h src/SwitchTask.cpp src/SwitchTask.h mock/MockDebugSystem.cpp mock/MockDebugSystem.h mock/MockCANSystem.cpp mock/MockCANSystem.h src/DebugSystem.h src/ChassisSystem.h src/CANSystem.h src/IMUSystem.h mock/MockIMUSystem.cpp mock/MockIMUSystem.h src/RotateAccumulator.cpp src/RotateAccumulator.h src/RemoteSystem.h mock/MockRemoteSystem.cpp mock/MockRemoteSystem.h)

add_executable(CAHRR_main main.cpp)
target_link_libraries(CAHRR_main CAHRR)
