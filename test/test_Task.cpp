//
// Created by Alex Chi on 2018/10/26.
//

//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "MockTask.h"

namespace {
    TEST(MockTaskTest, TestInitialize) {
        MockTask* task = new MockTask;
        task->update_count = 2333;
        ASSERT_TRUE(task->initialize());
        ASSERT_TRUE(task->initialized);
        ASSERT_EQ(task->update_count, 0);
        ASSERT_EQ(task->initialize_count, 1);
    }

    TEST(MockTaskTest, TestDestroy) {
        MockTask* task = new MockTask;
        ASSERT_TRUE(task->initialize());
        ASSERT_TRUE(task->destroy());
        ASSERT_FALSE(task->initialized);
        ASSERT_EQ(task->destroy_count, 1);
    }

    TEST(MockTaskTest, TestUpdate) {
        MockTask* task = new MockTask;
        ASSERT_TRUE(task->initialize());
        ASSERT_TRUE(task->update());
        ASSERT_EQ(task->update_count, 1);
        ASSERT_TRUE(task->update());
        ASSERT_EQ(task->update_count, 2);
    }
}

