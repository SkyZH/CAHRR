//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "AvgAccumulator.h"

namespace {
    TEST(AvgAccumulatorTest, TestReset) {
        AvgAccumulator<long long> *accumulator = new AvgAccumulator<long long>;
        accumulator->n = 233;
        accumulator->sum_data = 23333;
        accumulator->reset();
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }

    TEST(AvgAccumulatorTest, TestData) {
        AvgAccumulator<long long> *accumulator = new AvgAccumulator<long long>;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->n, 3);
        EXPECT_EQ(accumulator->sum_data, 9);
    }

    TEST(AvgAccumulatorTest, TestSum) {
        AvgAccumulator<long long> *accumulator = new AvgAccumulator<long long>;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->sum(), 3);
        EXPECT_EQ(accumulator->sum(), 0);
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }

    TEST(AvgAccumulatorTest, TestResetDouble) {
        AvgAccumulator<double> *accumulator = new AvgAccumulator<double>;
        accumulator->n = 233;
        accumulator->sum_data = 23333.3;
        accumulator->reset();
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }

    TEST(AvgAccumulatorTest, TestDataDouble) {
        AvgAccumulator<double> *accumulator = new AvgAccumulator<double>;
        accumulator->reset();
        accumulator->data(2.0);
        accumulator->data(3.0);
        accumulator->data(4.0);
        EXPECT_EQ(accumulator->n, 3);
        EXPECT_NEAR(accumulator->sum_data, 9.0, 1e-6);
    }

    TEST(AvgAccumulatorTest, TestSumDouble) {
        AvgAccumulator<double> *accumulator = new AvgAccumulator<double>;
        accumulator->reset();
        accumulator->data(3.0);
        accumulator->data(3.0);
        accumulator->data(4.0);
        EXPECT_NEAR(accumulator->sum(), 10.0/3.0, 1e-6);
        EXPECT_EQ(accumulator->sum(), 0);
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }
}
