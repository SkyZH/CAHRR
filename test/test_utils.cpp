//
// Created by Alex Chi on 2018/11/17.
//

#include "gtest/gtest.h"
#include "utils.h"

namespace {
    TEST(UtilsTest, TestClamp) {
        EXPECT_EQ(clamp(100, 50, 150), 100);
        EXPECT_EQ(clamp(1000, 50, 150), 150);
        EXPECT_EQ(clamp(0, 50, 150), 50);
    }

    TEST(UtilsTest, TestClampDouble) {
        EXPECT_EQ(clamp(100.0, 50.0, 150.0), 100.0);
        EXPECT_EQ(clamp(10.0, 50.0, 150.0), 50.0);
        EXPECT_EQ(clamp(200.0, 50.0, 150.0), 150.0);
    }

    TEST(UtilsTest, TestCycleErr) {
        EXPECT_EQ(cycle_err(100, 0, 0, 8192), 100);
        EXPECT_EQ(cycle_err(8000, 0, 0, 8192), -192);
        EXPECT_EQ(cycle_err(8000, 4000, 0, 8192), 4000);
        EXPECT_EQ(cycle_err(8192 * 2, 0, 0, 8192), 0);
        EXPECT_EQ(cycle_err(100, -300, 0, 8192), 400);
        EXPECT_EQ(cycle_err(100, 0, 100, 8192), 100);
        EXPECT_EQ(cycle_err(8000, 0, 100, 8192), -92);
        EXPECT_EQ(cycle_err(8000, 4000, 100, 8192), 4000);
        EXPECT_EQ(cycle_err(8192 * 2, 0, 100, 8292), 0);
        EXPECT_EQ(cycle_err(100, -300, 100, 8192), 400);
    }
}
