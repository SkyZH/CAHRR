//
// Created by Alex Chi on 2018/10/27.
//

#include "gtest/gtest.h"
#include "RotateAccumulator.h"

namespace {
    TEST(RotateAccumulatorTest, TestInitialize) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        EXPECT_TRUE(accumulator);
    }

    TEST(RotateAccumulatorTest, TestReset) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->reset();
        EXPECT_EQ(accumulator->get_overflow(), 0);
        EXPECT_EQ(accumulator->get_round(), 0);
    }

    TEST(RotateAccumulatorTest, TestSum) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);
        accumulator->data(233);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 233);

        accumulator->data(100);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 100);
    }

    TEST(RotateAccumulatorTest, TestContinousSum) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);
        accumulator->data(233);
        accumulator->data(456);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 456);
    }

    TEST(RotateAccumulatorTest, TestCycle) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);
        accumulator->data(2333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 2333);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 8191);

        accumulator->data(4200);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 4200);

        accumulator->data(3000);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 3000);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 8191);
    }


    TEST(RotateAccumulatorTest, TestCycle2) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);

        accumulator->data(7333);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 7333);

        accumulator->data(2333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 2333);

        accumulator->data(5333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 5333);

        accumulator->data(1132);
        EXPECT_EQ(accumulator->get_round(), 1);
        EXPECT_EQ(accumulator->get_overflow(), 1132);
    }

    TEST(RotateAccumulatorTest, TestZero) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);

        accumulator->data(0);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);
    }

    TEST(RotateAccumulatorTest, TestSelf) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 4096);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 4096);
    }

    TEST(RotateAccumulatorTest, TestCalibrate) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        EXPECT_EQ(accumulator->get_round(), 0);
        accumulator->data(0);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 4096);
        accumulator->calibrate();
        accumulator->data(5123);
        EXPECT_EQ(accumulator->offset_data, 5123);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 7165);
        accumulator->data(5123);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);
    }

    TEST(RotateAccumulatorTest, TestCalibrate2) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(0);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 4096);
        accumulator->calibrate();
        accumulator->data(2333);
        accumulator->data(4096);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 4096 - 2333);
        accumulator->data(5123);

        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 5123 - 2333);
    }

    TEST(RotateAccumulatorTest, TestCycleCalibrate) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(7333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);

        accumulator->data(2333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 3192);

        accumulator->data(5333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 6192);

        accumulator->data(332);
        EXPECT_EQ(accumulator->get_round(), 1);
        EXPECT_EQ(accumulator->get_overflow(), 1191);
    }

    TEST(RotateAccumulatorTest, TestCycleCalibrate2) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(2333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 5858);

        accumulator->data(4200);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 1867);

        accumulator->data(2200);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 8059);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 5858);
    }

    TEST(RotateAccumulatorTest, TestSweep) {
        RotateAccumulator *accumulator = new RotateAccumulator(8192);
        accumulator->data(2333);
        EXPECT_EQ(accumulator->get_round(), 0);
        EXPECT_EQ(accumulator->get_overflow(), 0);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 5858);

        accumulator->data(4200);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 1867);

        accumulator->data(2200);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 8059);

        accumulator->data(8191);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 5858);

        accumulator->data(0);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 5859);


        accumulator->data(2000);
        EXPECT_EQ(accumulator->get_round(), -2);
        EXPECT_EQ(accumulator->get_overflow(), 7859);

        accumulator->data(4000);
        EXPECT_EQ(accumulator->get_round(), -1);
        EXPECT_EQ(accumulator->get_overflow(), 1667);
    }
}

