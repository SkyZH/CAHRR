//
// Created by Alex Chi on 2018/10/26.
//

//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "Accumulator.h"

namespace {
    TEST(AccumulatorTest, TestReset) {
        Accumulator* accumulator = new Accumulator;
        accumulator->n = 233; accumulator->sum_data = 23333;
        accumulator->reset();
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }

    TEST(AccumulatorTest, TestData) {
        Accumulator* accumulator = new Accumulator;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->n, 3);
        EXPECT_EQ(accumulator->sum_data, 9);
    }

    TEST(AccumulatorTest, TestSum) {
        Accumulator* accumulator = new Accumulator;
        accumulator->reset();
        accumulator->data(2);
        accumulator->data(3);
        accumulator->data(4);
        EXPECT_EQ(accumulator->sum(), 3);
        EXPECT_EQ(accumulator->n, 0);
        EXPECT_EQ(accumulator->sum_data, 0);
    }
}

