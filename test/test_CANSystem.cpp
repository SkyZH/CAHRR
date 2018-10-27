//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "mock/MockCANSystem.h"

namespace {
    TEST(CANSystemTest, TestInitialize) {
        MockCANSystem* canSystem = new MockCANSystem;
    }
}

