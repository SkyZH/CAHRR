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

    class MockTimedMockTask : public TimedTask {
    public:
        MockTimedMockTask(unsigned int total_time) : TimedTask(total_time) {
            this->initialized = false;
            this->initialize_count = this->destroy_count = 0;
            this->update_count = 0;
        }

        bool initialize() {
            this->initialized = true;
            this->update_count = 0;
            this->initialize_count++;
            return TimedTask::initialize();
        }

        bool destroy() {
            this->initialized = false;
            this->destroy_count++;
            this->update_count = 0;
            return TimedTask::destroy();
        }

        bool update() {
            this->update_count++;
            return true;
        }

        virtual unsigned int time() {
            return task_time;
        }

        bool initialized;
        int update_count, initialize_count, destroy_count;
    };

    void sequence_time_test(MockTimedMockTask *task1, MockTimedMockTask *task2, MockTimedMockTask *task3, MockTimedMockTask *task4, SequentialTask* task) {
        // TIME: 0
        EXPECT_FALSE(task1->isEnd());
        EXPECT_FALSE(task2->isEnd());
        EXPECT_FALSE(task3->isEnd());
        EXPECT_FALSE(task4->isEnd());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->isEnd());
        EXPECT_FALSE(task2->isEnd());
        EXPECT_FALSE(task3->isEnd());
        EXPECT_FALSE(task4->isEnd());

        task_time += 1;
        // TIME: 1
        EXPECT_TRUE(task1->isEnd());
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        task_time += 1;
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);

        task_time += 1;
        // TIME: 3
        EXPECT_TRUE(task2->isEnd());
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        task_time += 3;
        // TIME: 6
        EXPECT_TRUE(task3->isEnd());
        EXPECT_FALSE(task->isEnd());
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);

        task_time += 4;
        EXPECT_FALSE(task->isEnd());
        ASSERT_TRUE(task->update());
    }

    TEST_F(TimedTaskTest, TestWithSequentialTask) {
        MockTimedMockTask *task1 = new MockTimedMockTask(1);
        MockTimedMockTask *task2 = new MockTimedMockTask(2);
        MockTimedMockTask *task3 = new MockTimedMockTask(3);
        MockTimedMockTask *task4 = new MockTimedMockTask(4);
        SequentialTask *task = new SequentialTask(std::vector<Task*>({ task1, task2, task3, task4 }));
        task_time = 0;
        ASSERT_TRUE(task->initialize());
        sequence_time_test(task1, task2, task3, task4, task);
        EXPECT_FALSE(task->isEnd());
    }

    TEST_F(TimedTaskTest, TestWithSequentialTaskNonCycle) {
        MockTimedMockTask *task1 = new MockTimedMockTask(1);
        MockTimedMockTask *task2 = new MockTimedMockTask(2);
        MockTimedMockTask *task3 = new MockTimedMockTask(3);
        MockTimedMockTask *task4 = new MockTimedMockTask(4);
        SequentialTask *task = new SequentialTask(std::vector<Task*>({ task1, task2, task3, task4 }), false);
        task_time = 0;
        ASSERT_TRUE(task->initialize());
        sequence_time_test(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->isEnd());
    }
}
