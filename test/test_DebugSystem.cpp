//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "mock/MockDebugSystem.h"
#include <string>

namespace {
    TEST(DebugSystemTest, TestInitialize) {
        MockDebugSystem *debugSystem = new MockDebugSystem;
        EXPECT_TRUE(debugSystem->initialize());
        EXPECT_EQ(logged_data, "[DebugSystem][I] 0 system initialized");
    }

    TEST(DebugSystemTest, TestInfo) {
        MockDebugSystem *debugSystem = new MockDebugSystem;
        EXPECT_TRUE(debugSystem->initialize());
        EXPECT_TRUE(debugSystem->info("MockSystem", "test message"));
        EXPECT_EQ(logged_data, "[MockSystem][I] 0 test message");
        EXPECT_TRUE(debugSystem->info(std::string("MockSystem"), "test message 2"));
        EXPECT_EQ(logged_data, "[MockSystem][I] 0 test message 2");
    }

    TEST(DebugSystemTest, TestError) {
        MockDebugSystem *debugSystem = new MockDebugSystem;
        EXPECT_TRUE(debugSystem->initialize());
        EXPECT_TRUE(debugSystem->error("MockSystem", "test message"));
        EXPECT_EQ(logged_data, "[MockSystem][E] 0 test message");
        EXPECT_TRUE(debugSystem->error(std::string("MockSystem"), "test message 2"));
        EXPECT_EQ(logged_data, "[MockSystem][E] 0 test message 2");
    }

    TEST(DebugSystemTest, TestDestroy) {
        MockDebugSystem *debugSystem = new MockDebugSystem;
        EXPECT_TRUE(debugSystem->initialize());
        EXPECT_TRUE(debugSystem->destroy());
        EXPECT_EQ(logged_data, "[DebugSystem][I] 0 system halted");
    }
}

