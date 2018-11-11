//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "ConditionSwitchTask.h"
#include "MockTask.h"

namespace {
    bool selected = false;
    class ConditionSwitchTaskTest : public ::testing::Test {
    protected:

        ConditionSwitchTaskTest() {
        }

        ~ConditionSwitchTaskTest() override {
        }

        void SetUp() override {
            selected = false;
        }
    };

    class MockConditionSwitchTask : public ConditionSwitchTask {
    public:
        MockConditionSwitchTask(Task* task1, Task* task2) : ConditionSwitchTask(task1, task2) {

        }
        bool when() {
            return selected;
        }
    };
    TEST(ConditionSwitchTaskTest, TestInitialize) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        selected = false;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
    }

    TEST(ConditionSwitchTaskTest, TestInitializeReverse) {
        MockTask *task1 = new MockTask;
        MockTask *task2 = new MockTask;
        MockConditionSwitchTask* task = new MockConditionSwitchTask(task1, task2);
        selected = true;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
    }

    TEST(ConditionSwitchTaskTest, TestDestroy) {

    }

    TEST(ConditionSwitchTaskTest, TestUpdate) {
    }
}

