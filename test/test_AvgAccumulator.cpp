//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "AvgAccumulator.h"

namespace {
    TEST(AvgAccumulatorTest, TestReset) {
        AvgAccumulator *accumulator = new AvgAccumulator;
        accumulator->n = 233;
        accumulator->sum_data = 23333;
        accumulator->reset();
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }

    TEST(AvgAccumulatorTest, TestData) {
        AvgAccumulator *accumulator = new AvgAccumulator;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->n, 3);
        EXPECT_EQ(accumulator->sum_data, 9);
    }

    TEST(AvgAccumulatorTest, TestSum) {
        AvgAccumulator *accumulator = new AvgAccumulator;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->sum(), 3);
        EXPECT_EQ(accumulator->sum(), 0);
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }
}

