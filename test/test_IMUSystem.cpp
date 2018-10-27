//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "mock/MockIMUSystem.h"

namespace {
    TEST(IMUSystemTest, TestInitialize) {
        MockIMUSystem *imuSystem = new MockIMUSystem;
        EXPECT_TRUE(imuSystem->initialize());
    }

    TEST(IMUSystemTest, TestDestroy) {
        MockIMUSystem *imuSystem = new MockIMUSystem;
        EXPECT_TRUE(imuSystem->initialize());
        EXPECT_TRUE(imuSystem->destroy());
    }

    TEST(IMUSystemTest, TestUpdate) {
        MockIMUSystem *imuSystem = new MockIMUSystem;
        EXPECT_TRUE(imuSystem->initialize());
        EXPECT_TRUE(imuSystem->update());
    }

    TEST(IMUSystemTest, TestData) {
        MockIMUSystem *imuSystem = new MockIMUSystem;
        EXPECT_TRUE(imuSystem->initialize());
        imu_data[1] = 2333;
        EXPECT_TRUE(imuSystem->update());
        EXPECT_EQ(imuSystem->get(1), 2333);
    }

}

