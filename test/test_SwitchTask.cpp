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
        ASSERT_TRUE(task->initialize(true));
        ASSERT_EQ(task->selected, true);
        ASSERT_TRUE(mockTask->initialized);
    }

    TEST(SwitchTaskTest, TestUpdate) {
        MockTask *mockTask = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask, new MockTask);
        ASSERT_TRUE(task->initialize(false));
        ASSERT_TRUE(task->update());
        ASSERT_EQ(mockTask->update_count, 1);
        ASSERT_TRUE(task->update());
        ASSERT_EQ(mockTask->update_count, 2);
    }

    TEST(SwitchTaskTest, TestSwitch) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        ASSERT_TRUE(task->initialize(false));
        ASSERT_TRUE(mockTask1->initialized);
        ASSERT_FALSE(mockTask2->initialized);
        ASSERT_TRUE(task->update());
        ASSERT_EQ(mockTask1->update_count, 1);
        ASSERT_EQ(mockTask2->update_count, 0);
        ASSERT_TRUE(task->select(true));
        ASSERT_EQ(task->selected, true);
        ASSERT_FALSE(mockTask1->initialized);
        ASSERT_TRUE(mockTask2->initialized);
        ASSERT_TRUE(task->update());
        ASSERT_EQ(mockTask1->update_count, 0);
        ASSERT_EQ(mockTask2->update_count, 1);
    }

    TEST(SwitchTaskTest, TestDestroy) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        ASSERT_TRUE(task->initialize(false));
        ASSERT_TRUE(mockTask1->initialized);
        ASSERT_FALSE(mockTask2->initialized);
        ASSERT_TRUE(task->destroy());
        ASSERT_FALSE(mockTask1->initialized);
        ASSERT_FALSE(mockTask2->initialized);
        ASSERT_TRUE(task->initialize(true));
        ASSERT_FALSE(mockTask1->initialized);
        ASSERT_TRUE(mockTask2->initialized);
        ASSERT_TRUE(task->destroy());
        ASSERT_FALSE(mockTask1->initialized);
        ASSERT_FALSE(mockTask2->initialized);
    }

    TEST(SwitchTaskTest, TestSelfSwitch) {
        MockTask *mockTask1 = new MockTask;
        MockTask *mockTask2 = new MockTask;
        SwitchTask *task = new SwitchTask(mockTask1, mockTask2);
        ASSERT_TRUE(task->initialize(false));
        ASSERT_TRUE(mockTask1->initialized);
        ASSERT_FALSE(mockTask2->initialized);
        ASSERT_TRUE(task->select(false));
        ASSERT_EQ(mockTask1->initialize_count, 1);
        ASSERT_EQ(mockTask1->destroy_count, 0);
    }

}

