//
// Created by Alex Chi on 2018/10/26.
//

#include "gtest/gtest.h"
#include "SwitchTask.h"
#include "MockTask.h"

namespace {
    TEST(SwitchTaskTest, TestInitialize) {
        MockTask *mockTask = new MockTask;
        SwitchTask *task = new SwitchTask(new MockTask, mockTask);
        EXPECT_TRUE(task->initialize(true));
        EXPECT_EQ(task->selected, true);
        EXPECT_TRUE(mockTask->initialized);
    }

    TEST(SwitchTaskTest, TestUpdate) {
        MockTask *mockTask = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask, new MockTask);
        EXPECT_TRUE(task->initialize(false));
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask->update_count, 1);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask->update_count, 2);
    }

    TEST(SwitchTaskTest, TestSwitch) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        EXPECT_TRUE(task->initialize(false));
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask1->update_count, 1);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_TRUE(task->select(true));
        EXPECT_EQ(task->selected, true);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_EQ(mockTask2->update_count, 1);
    }

    TEST(SwitchTaskTest, TestDestroy) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        EXPECT_TRUE(task->initialize(false));
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_TRUE(task->initialize(true));
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
    }

    TEST(SwitchTaskTest, TestSelfSwitch) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        EXPECT_TRUE(task->initialize(false));
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_TRUE(task->select(false));
        EXPECT_EQ(mockTask1->initialize_count, 1);
        EXPECT_EQ(mockTask1->destroy_count, 0);
    }

}

