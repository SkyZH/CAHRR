//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "ChassisSystem.h"

namespace {
    TEST(ChassisSystemTest, TestInitialize) {
        ChassisSystem* chassisSystem = new ChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_EQ(chassis_sent_data_bf, 0);
        EXPECT_EQ(chassis_sent_data_lr, 0);
    }

    TEST(ChassisSystemTest, TestMultipleInitialize) {
        ChassisSystem* chassisSystem = new ChassisSystem();
        EXPECT_TRUE(chassisSystem->initialize());
        EXPECT_FALSE(chassisSystem->initialize());
    }

    TEST(ChassisSystemTest, TestDestroy) {
        ChassisSystem* chassisSystem = new ChassisSystem();
        EXPECT_FALSE(chassisSystem->destroy());
        chassisSystem->initialize();
        chassis_sent_data_bf = 233;
        chassis_sent_data_lr = 233;
        EXPECT_TRUE(chassisSystem->destroy());
        EXPECT_EQ(chassis_sent_data_bf, 0);
        EXPECT_EQ(chassis_sent_data_lr, 0);
    }

    TEST(ChassisSystemTest, TestUpdate) {
        ChassisSystem* chassisSystem = new ChassisSystem();
        chassisSystem->BackForward = 2;
        chassisSystem->LeftRight = 3;
        EXPECT_TRUE(chassisSystem->update());
        EXPECT_EQ(chassis_sent_data_bf, 2);
        EXPECT_EQ(chassis_sent_data_lr, 3);
    }

    TEST(ChassisSystemTest, TestData) {
        ChassisSystem* chassisSystem = new ChassisSystem();
        chassisSystem->initialize();
        EXPECT_TRUE(chassisSystem->data());
    }
}

