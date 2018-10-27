cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

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

add_executable(CAHRR_test test_main.cpp test_ChassisSystem.cpp test_Accumulator.cpp test_SwitchTask.cpp test_Task.cpp test_DebugSystem.cpp test_CANSystem.cpp)
target_link_libraries(CAHRR_test CAHRR gtest gtest_main)
gtest_discover_tests(CAHRR_test)
