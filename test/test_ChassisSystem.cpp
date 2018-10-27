//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "mock/MockChassisSystem.h"

namespace {
    TEST(ChassisSystemTest, TestInitialize) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_EQ(chassis_sent_data_bf, 0);
        EXPECT_EQ(chassis_sent_data_lr, 0);
    }

    TEST(ChassisSystemTest, TestMultipleInitialize) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_FALSE(chassisSystem->initialize());
    }

    TEST(ChassisSystemTest, TestDestroy) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_FALSE(chassisSystem->destroy());
        EXPECT_TRUE(chassisSystem->initialize());
        chassis_sent_data_bf = 233;
        chassis_sent_data_lr = 233;
        EXPECT_TRUE(chassisSystem->destroy());
        EXPECT_EQ(chassis_sent_data_bf, 0);
        EXPECT_EQ(chassis_sent_data_lr, 0);
    }

    TEST(ChassisSystemTest, TestUpdate) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        chassisSystem->BackForward = 2;
        chassisSystem->LeftRight = 3;
        EXPECT_TRUE(chassisSystem->update());
        EXPECT_EQ(chassis_sent_data_bf, 2);
        EXPECT_EQ(chassis_sent_data_lr, 3);
    }

    TEST(ChassisSystemTest, TestData) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_TRUE(chassisSystem->data());
    }

    TEST(ChassisSystemTest, TestSetSpeed) {
        MockChassisSystem *chassisSystem = new MockChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_TRUE(chassisSystem->setSpeed(1, 3));
        EXPECT_EQ(chassisSystem->LeftRight, 3);
        EXPECT_EQ(chassisSystem->BackForward, 1);
    }
}

