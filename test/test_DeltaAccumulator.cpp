//
// Created by Alex Chi on 2018/11/13.
//

#include "gtest/gtest.h"
#include "DeltaAccumulator.h"

namespace {
    TEST(DeltaAccumulatorTest, TestReset) {
        DeltaAccumulator<long long> *accumulator = new DeltaAccumulator<long long>;
        accumulator->reset();
        EXPECT_EQ(accumulator->do_reset, true);
    }

    TEST(DeltaAccumulatorTest, TestData) {
        DeltaAccumulator<long long> *accumulator = new DeltaAccumulator<long long>;
        accumulator->reset();
        accumulator->delta(2333);
        EXPECT_EQ(accumulator->do_reset, false);
        EXPECT_EQ(accumulator->lst_data, 2333);
    }

    TEST(DeltaAccumulatorTest, TestDelta) {
        DeltaAccumulator<long long> *accumulator = new DeltaAccumulator<long long>;
        accumulator->reset();
        EXPECT_EQ(accumulator->delta(2333), 0);
        accumulator->reset();
        EXPECT_EQ(accumulator->delta(23333), 0);
        EXPECT_EQ(accumulator->delta(33333), 10000);
    }
    TEST(DeltaAccumulatorTest, TestResetDouble) {
        DeltaAccumulator<double> *accumulator = new DeltaAccumulator<double>;
        accumulator->reset();
        EXPECT_EQ(accumulator->do_reset, true);
    }

    TEST(DeltaAccumulatorTest, TestDataDouble) {
        DeltaAccumulator<double> *accumulator = new DeltaAccumulator<double>;
        accumulator->reset();
        accumulator->delta(2333.233);
        EXPECT_EQ(accumulator->do_reset, false);
        EXPECT_NEAR(accumulator->lst_data, 2333.233, 1e-6);
    }

    TEST(DeltaAccumulatorTest, TestDeltaDouble) {
        DeltaAccumulator<double> *accumulator = new DeltaAccumulator<double>;
        accumulator->reset();
        EXPECT_NEAR(accumulator->delta(2333.233), 0, 1e-6);
        accumulator->reset();
        EXPECT_NEAR(accumulator->delta(23333.233), 0, 1e-6);
        EXPECT_NEAR(accumulator->delta(33333.533), 10000.3, 1e-6);
    }
}
