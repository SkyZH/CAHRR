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
        EXPECT_EQ(clamp(100.0, 50.0, 150.0), 100.0);
        EXPECT_EQ(clamp(10.0, 50.0, 150.0), 50.0);
        EXPECT_EQ(clamp(200.0, 50.0, 150.0), 150.0);
    }
}
