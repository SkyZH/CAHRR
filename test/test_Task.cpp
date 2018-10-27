//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "MockTask.h"

#define CAHRR_MOCK_INCLUDED

namespace {
    TEST(MockTaskTest, TestInitialize) {
        MockTask *task = new MockTask;
        task->update_count = 2333;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->initialized);
        EXPECT_EQ(task->update_count, 0);
        EXPECT_EQ(task->initialize_count, 1);
    }

    TEST(MockTaskTest, TestDestroy) {
        MockTask *task = new MockTask;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(task->initialized);
        EXPECT_EQ(task->destroy_count, 1);
    }

    TEST(MockTaskTest, TestUpdate) {
        MockTask *task = new MockTask;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task->update_count, 1);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task->update_count, 2);
    }
}

