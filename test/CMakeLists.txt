cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

include(GoogleTest)

enable_testing()

set(UNIT_TESTS_INCLUDES .. ../src ../mock)

include_directories(${UNIT_TESTS_INCLUDES})

add_executable(CAHRR_test test_main.cpp test_ChassisSystem.cpp test_AvgAccumulator.cpp test_SwitchTask.cpp test_Task.cpp test_DebugSystem.cpp test_CANSystem.cpp test_IMUSystem.cpp test_RotateAccumulator.cpp test_RemoteSystem.cpp test_PIDAccumulator.cpp test_RampAccumulator.cpp test_AutoSwitchTask.cpp test_ConditionSwitchTask.cpp test_TriggerSwitchTask.cpp test_TimedTask.cpp test_SequentialTask.cpp test_ParallelTask.cpp)
target_link_libraries(CAHRR_test CAHRR CAHRR_mock gtest gtest_main)
gtest_discover_tests(CAHRR_test)
