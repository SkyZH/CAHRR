//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "mock/MockCANSystem.h"

namespace {
    TEST(CANSystemTest, TestInitialize) {
        MockCANSystem *canSystem = new MockCANSystem;
        EXPECT_TRUE(canSystem->initialize());
    }

    TEST(CANSystemTest, TestDestroy) {
        MockCANSystem *canSystem = new MockCANSystem;
        EXPECT_TRUE(canSystem->initialize());
        EXPECT_TRUE(canSystem->destroy());
    }

    TEST(CANSystemTest, TestData) {
        MockCANSystem *canSystem = new MockCANSystem;
        EXPECT_TRUE(canSystem->data());
    }

    TEST(CANSystemTest, TestSet) {
        MockCANSystem *canSystem = new MockCANSystem;
        EXPECT_TRUE(canSystem->set(1, 2));
        EXPECT_NE(can_sent_data[1], 2);
    }

    TEST(CANSystemTest, TestUpdate) {
        MockCANSystem *canSystem = new MockCANSystem;
        EXPECT_TRUE(canSystem->set(1, 4));
        EXPECT_TRUE(canSystem->set(2, 3));
        EXPECT_TRUE(canSystem->update());
        EXPECT_EQ(can_sent_data[1], 4);
        EXPECT_EQ(can_sent_data[2], 3);
    }

    TEST(CANSystemTest, TestGet) {
        MockCANSystem *canSystem = new MockCANSystem;
        can_received_data[1 + 1] = 3;
        EXPECT_TRUE(canSystem->data());
        EXPECT_TRUE(canSystem->update());
        EXPECT_EQ(canSystem->get(1, 1), 3);
    }

}

