//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "TriggerSwitchTask.h"
#include "MockTask.h"

namespace {
    bool task_triggered = false;
    class TriggerSwitchTaskTest : public ::testing::Test {
    protected:

        TriggerSwitchTaskTest() {
        }

        ~TriggerSwitchTaskTest() override {
        }

        void SetUp() override {
            task_triggered = false;
        }
    };

    class MockTriggerSwitchTask : public TriggerSwitchTask {
    public:
        MockTriggerSwitchTask(Task* task1, Task* task2) : TriggerSwitchTask(task1, task2) {

        }
        bool trigger() {
            return task_triggered;
        }
    };
    TEST_F(TriggerSwitchTaskTest, TestInitialize) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTriggerSwitchTask* task = new MockTriggerSwitchTask(task0, task1);
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
    }

    TEST_F(TriggerSwitchTaskTest, TestDestroy) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTriggerSwitchTask* task = new MockTriggerSwitchTask(task0, task1);
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
    }

    TEST_F(TriggerSwitchTaskTest, TestUpdate) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTriggerSwitchTask* task = new MockTriggerSwitchTask(task0, task1);
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 1);
        EXPECT_EQ(task1->update_count, 0);

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 2);
        EXPECT_EQ(task1->update_count, 0);
    }

    void test_trigger_sequence(MockTask* task0, MockTask* task1, TriggerSwitchTask* task) {
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 1);
        EXPECT_EQ(task1->update_count, 0);

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 2);
        EXPECT_EQ(task1->update_count, 0);

        task_triggered = true;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task0->initialized);
        EXPECT_TRUE(task1->initialized);
        EXPECT_EQ(task0->update_count, 0);
        EXPECT_EQ(task1->update_count, 1);

        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task0->initialized);
        EXPECT_TRUE(task1->initialized);
        EXPECT_EQ(task0->update_count, 0);
        EXPECT_EQ(task1->update_count, 2);

        task_triggered = false;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task0->initialized);
        EXPECT_TRUE(task1->initialized);
        EXPECT_EQ(task0->update_count, 0);
        EXPECT_EQ(task1->update_count, 3);

        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task0->initialized);
        EXPECT_TRUE(task1->initialized);
        EXPECT_EQ(task0->update_count, 0);
        EXPECT_EQ(task1->update_count, 4);

        task_triggered = true;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 1);
        EXPECT_EQ(task1->update_count, 0);

        task_triggered = false;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_EQ(task0->update_count, 2);
        EXPECT_EQ(task1->update_count, 0);

        task_triggered = true;
        EXPECT_TRUE(task->update());
        task_triggered = false;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task0->initialized);
        EXPECT_TRUE(task1->initialized);

        task_triggered = true;
        EXPECT_TRUE(task->update());
        task_triggered = false;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task0->initialized);
        EXPECT_FALSE(task1->initialized);

        EXPECT_TRUE(task->destroy());
    }

    TEST_F(TriggerSwitchTaskTest, TestTrigger) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTriggerSwitchTask* task = new MockTriggerSwitchTask(task0, task1);
        test_trigger_sequence(task0, task1, task);
    }

    TEST_F(TriggerSwitchTaskTest, TestTriggerMultiple) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTriggerSwitchTask* task = new MockTriggerSwitchTask(task0, task1);
        test_trigger_sequence(task0, task1, task);
        test_trigger_sequence(task0, task1, task);
        test_trigger_sequence(task0, task1, task);
    }
}

