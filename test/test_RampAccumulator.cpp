//
// Created by Alex Chi on 2018/10/29.
//

#include "gtest/gtest.h"
#include "RampAccumulator.h"

namespace {
    TEST(RampAccumulatorTest, TestInitialize) {
        RampAccumulator *ramp = new RampAccumulator(100);
        EXPECT_EQ(ramp->do_reset, true);
        EXPECT_EQ(ramp->calc(23333), 23333);
        EXPECT_EQ(ramp->ramp_limit, 100);
    }
    TEST(RampAccumulatorTest, TestReset) {
        RampAccumulator *ramp = new RampAccumulator(100);
        ramp->data(2333);
        ramp->reset();
        EXPECT_EQ(ramp->do_reset, true);
        ramp->data(2333);
        EXPECT_EQ(ramp->do_reset, false);
    }
    TEST(RampAccumulatorTest, TestCalc) {
        RampAccumulator *ramp = new RampAccumulator(100);
        EXPECT_EQ(ramp->calc(10), 10);
        ramp->data(10);
        EXPECT_EQ(ramp->calc(10), 10);
        EXPECT_EQ(ramp->calc(100), 100);
        EXPECT_EQ(ramp->calc(1000), 110);
        EXPECT_EQ(ramp->calc(-10), -10);
        EXPECT_EQ(ramp->calc(-100), -90);
    }
}

