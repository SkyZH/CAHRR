//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "mock/MockCANSystem.h"

namespace {
    TEST(CANSystemTest, TestInitialize) {
        MockCANSystem *canSystem = new MockCANSystem;
        ASSERT_TRUE(canSystem->initialize());
    }

    TEST(CANSystemTest, TestDestroy) {
        MockCANSystem *canSystem = new MockCANSystem;
        ASSERT_TRUE(canSystem->destroy());
    }

    TEST(CANSystemTest, TestData) {
        MockCANSystem *canSystem = new MockCANSystem;
        ASSERT_TRUE(canSystem->data());
    }

    TEST(CANSystemTest, TestSet) {
        MockCANSystem *canSystem = new MockCANSystem;
        ASSERT_TRUE(canSystem->set(1, 2));
        ASSERT_NE(can_sent_data[1], 2);
    }

    TEST(CANSystemTest, TestUpdate) {
        MockCANSystem *canSystem = new MockCANSystem;
        ASSERT_TRUE(canSystem->set(1, 4));
        ASSERT_TRUE(canSystem->set(2, 3));
        ASSERT_TRUE(canSystem->update());
        ASSERT_EQ(can_sent_data[1], 4);
        ASSERT_EQ(can_sent_data[2], 3);
    }

    TEST(CANSystemTest, TestGet) {
        MockCANSystem *canSystem = new MockCANSystem;
        can_received_data[1 + 1] = 3;
        ASSERT_TRUE(canSystem->data());
        ASSERT_TRUE(canSystem->update());
        ASSERT_EQ(canSystem->get(1, 1), 3);
    }

}

