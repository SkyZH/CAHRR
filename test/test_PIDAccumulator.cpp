//
// Created by Alex Chi on 2018/10/29.
//

#include "gtest/gtest.h"
#include "PIDAccumulator.h"

namespace {
    TEST(PIDDisplacementAccumulatorTest, TestInitialize) {
        PIDDisplacementAccumulator *pid = new PIDDisplacementAccumulator;
        EXPECT_TRUE(pid->set_pid(1.0, 1.0, 1.0));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
    }
    TEST(PIDRateAccumulatorTest, TestInitialize) {
        PIDRateAccumulator *pid = new PIDRateAccumulator;
        EXPECT_TRUE(pid->set_pid(1.0, 1.0, 1.0));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
    }
    TEST(PIDDisplacementAccumulatorTest, TestReset) {
        PIDDisplacementAccumulator *pid = new PIDDisplacementAccumulator;
        EXPECT_TRUE(pid->set_pid(1.0, 1.0, 1.0));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
        EXPECT_TRUE(pid->reset());
    }
    TEST(PIDRateAccumulatorTest, TestReset) {
        PIDRateAccumulator *pid = new PIDRateAccumulator;
        EXPECT_TRUE(pid->set_pid(5, 5, 5));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
        EXPECT_TRUE(pid->reset());
    }
    TEST(PIDDisplacementAccumulatorTest, TestCalc) {
        PIDDisplacementAccumulator *pid = new PIDDisplacementAccumulator;
        EXPECT_TRUE(pid->set_pid(5, 5, 5));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
        EXPECT_TRUE(pid->reset());
        EXPECT_GT(pid->calc(1), 0);
        EXPECT_LT(pid->calc(0.5), 0);
        EXPECT_GT(pid->calc(0.1), 0);
    }
    TEST(PIDRateAccumulatorTest, TestCalc) {
        PIDRateAccumulator *pid = new PIDRateAccumulator;
        EXPECT_TRUE(pid->set_pid(5, 5, 5));
        EXPECT_TRUE(pid->set_output(-300.0, 300.0));
        EXPECT_TRUE(pid->reset());
        EXPECT_GT(pid->calc(1), 0);
        EXPECT_LT(pid->calc(0.5), 0);
        EXPECT_GT(pid->calc(0.1), 0);
    }
}
