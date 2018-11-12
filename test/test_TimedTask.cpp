//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "MockTask.h"
#include "TimedTask.h"
#include "AutoSwitchTask.h"
#include "SequentialTask.h"

namespace {
    unsigned int task_time = 0;
    class TimedTaskTest : public ::testing::Test {
    protected:
        TimedTaskTest() {
        }

        ~TimedTaskTest() override {
        }

        void SetUp() override {
            task_time = 0;
        }
    };

    class MockTimedTask : public TimedTask {
    public:
        MockTimedTask(unsigned int total_time) : TimedTask(total_time) {
        }

        virtual unsigned int time() {
            return task_time;
        }

        virtual bool update() {
            return true;
        }
    };

    TEST_F(TimedTaskTest, TestInitialize) {
        MockTimedTask *task = new MockTimedTask(5);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
    }

    TEST_F(TimedTaskTest, TestIsEnd) {
        MockTimedTask *task = new MockTimedTask(5);
        EXPECT_FALSE(task->isEnd());
    }

    TEST_F(TimedTaskTest, TestUpdate) {
        MockTimedTask *task = new MockTimedTask(5);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        task_time = 1;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 3;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 5;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
    }

    TEST_F(TimedTaskTest, TestUpdateMulti) {
        MockTimedTask *task = new MockTimedTask(5);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        task_time = 1;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 3;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 5;
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());

        EXPECT_FALSE(task->isEnd());

        task_time = 10;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        task_time = 12;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 14;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        task_time = 15;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(TimedTaskTest, TestWithSequentialTask) {
        
    }
}

