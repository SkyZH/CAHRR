//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "ConditionSwitchTask.h"
#include "MockTask.h"

namespace {
    bool task_selected = false;
    class ConditionSwitchTaskTest : public ::testing::Test {
    protected:

        ConditionSwitchTaskTest() {
        }

        ~ConditionSwitchTaskTest() override {
        }

        void SetUp() override {
            task_selected = false;
        }
    };

    class MockConditionSwitchTask : public ConditionSwitchTask {
    public:
        MockConditionSwitchTask(Task* task1, Task* task2) : ConditionSwitchTask(task1, task2) {

        }
        bool when() {
            return task_selected;
        }
    };
    TEST_F(ConditionSwitchTaskTest, TestInitialize) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        task_selected = false;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
    }

    TEST_F(ConditionSwitchTaskTest, TestInitializeReverse) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        task_selected = true;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
    }

    TEST_F(ConditionSwitchTaskTest, TestDestroy) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        task_selected = true;
        EXPECT_TRUE(task->initialize());
        task_selected = false;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
    }

    void update_test_sequence(MockTask* task1, MockTask* task2, MockConditionSwitchTask* task) {
        task_selected = true;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task1->update_count, 0);
        EXPECT_EQ(task2->update_count, 1);
        task_selected = false;
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_EQ(task2->update_count, 0);
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(ConditionSwitchTaskTest, TestUpdate) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        update_test_sequence(task1, task2, task);
    }

    TEST_F(ConditionSwitchTaskTest, TestUpdateMultiple) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        update_test_sequence(task1, task2, task);
        update_test_sequence(task1, task2, task);
    }
}

