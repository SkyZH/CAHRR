//
// Created by Alex Chi on 2018/11/13.
//

#include "gtest/gtest.h"
#include "mock/MockUltrasonicSystem.h"
#include "UltrasonicSystem.h"

extern bool ultrasonic_data_sent;
extern int now_time;

namespace {
    TEST(UltrasonicSystemTest, TestInitialize) {
        MockUltrasonicSystem *usSystem = new MockUltrasonicSystem;
        EXPECT_TRUE(usSystem->initialize());
    }

    TEST(UltrasonicSystemTest, TestDestroy) {
        MockUltrasonicSystem *usSystem = new MockUltrasonicSystem;
        ASSERT_TRUE(usSystem->initialize());
        EXPECT_TRUE(usSystem->destroy());
    }

    TEST(UltrasonicSystemTest, TestTrigger) {
        MockUltrasonicSystem *usSystem = new MockUltrasonicSystem;
        ASSERT_TRUE(usSystem->initialize());
        ultrasonic_data_sent = false;
        EXPECT_TRUE(usSystem->trigger());
        EXPECT_TRUE(ultrasonic_data_sent);
    }

    TEST(UltrasonicSystemTest, TestFailsafeGet) {
        MockUltrasonicSystem *usSystem = new MockUltrasonicSystem;
        ASSERT_TRUE(usSystem->initialize());
        EXPECT_TRUE(usSystem->update());
        now_time = 0;
        EXPECT_EQ(usSystem->time(), 0);
        EXPECT_TRUE(ultrasonic_data_sent);
        ultrasonic_data_sent = false;
        now_time = 100;
        ASSERT_TRUE(usSystem->trigger());
        EXPECT_TRUE(ultrasonic_data_sent);
        now_time = 200;
        ASSERT_TRUE(usSystem->trigger());
        EXPECT_TRUE(usSystem->update());

        EXPECT_EQ(usSystem->time(), 100);
        now_time = 400;
        ASSERT_TRUE(usSystem->trigger());
        EXPECT_TRUE(usSystem->update());
        EXPECT_EQ(usSystem->time(), 200);
        EXPECT_TRUE(usSystem->update());
        EXPECT_EQ(usSystem->time(), 0);
    }

}

