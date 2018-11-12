//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "MockTask.h"
#include "TimedTask.h"
#include "SequentialTask.h"
#include <vector>

namespace {
    unsigned int task_time = 0;
    class SequentialTaskTest : public ::testing::Test {
    protected:
        SequentialTaskTest() {
        }

        ~SequentialTaskTest() override {
        }

        void SetUp() override {
            task_time = 0;
        }
    };

    class TimedMockTask : public TimedTask {
    public:
        TimedMockTask(unsigned int total_time) : TimedTask(total_time) {
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



    TEST_F(SequentialTaskTest, TestInitialize) {
        TimedMockTask *task1 = new TimedMockTask(2);
        TimedMockTask *task2 = new TimedMockTask(3);
        TimedMockTask *task3 = new TimedMockTask(4);
        TimedMockTask *task4 = new TimedMockTask(5);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
    }

    TEST_F(SequentialTaskTest, TestUpdate) {
        TimedMockTask *task1 = new TimedMockTask(2);
        TimedMockTask *task2 = new TimedMockTask(3);
        TimedMockTask *task3 = new TimedMockTask(4);
        TimedMockTask *task4 = new TimedMockTask(5);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->initialize_count, 0);
        EXPECT_EQ(task1->initialize_count, 1);
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_TRUE(task1->initialized);

        task_time = 2;
        EXPECT_TRUE(task1->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->initialize_count, 1);
        EXPECT_EQ(task1->initialize_count, 1);
        EXPECT_EQ(task2->update_count, 1);

        task_time = 2 + 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);

        task_time = 2 + 3 + 4;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        EXPECT_EQ(task4->update_count, 1);

        task_time = 2 + 3 + 4 + 5;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task1->update_count, 3);
    }

    void test_sequence_update(TimedMockTask* task1, TimedMockTask* task2, TimedMockTask* task3, TimedMockTask* task4, SequentialTask* task) {
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_FALSE(task->isEnd());

        task_time += 2;
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->update_count, 1);
        EXPECT_FALSE(task->isEnd());

        task_time += 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);
        EXPECT_FALSE(task->isEnd());

        task_time += 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 4);
        EXPECT_FALSE(task->isEnd());

        task_time += 1;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        EXPECT_EQ(task4->update_count, 3);
        EXPECT_FALSE(task->isEnd());

        task_time += 5;
    }

    TEST_F(SequentialTaskTest, TestUpdateMulti) {
        TimedMockTask *task1 = new TimedMockTask(2);
        TimedMockTask *task2 = new TimedMockTask(3);
        TimedMockTask *task3 = new TimedMockTask(4);
        TimedMockTask *task4 = new TimedMockTask(5);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        test_sequence_update(task1, task2, task3, task4, task);
        test_sequence_update(task1, task2, task3, task4, task);
        test_sequence_update(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestUpdateNoCycle) {
        TimedMockTask *task1 = new TimedMockTask(2);
        TimedMockTask *task2 = new TimedMockTask(3);
        TimedMockTask *task3 = new TimedMockTask(4);
        TimedMockTask *task4 = new TimedMockTask(5);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }), false);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        test_sequence_update(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestDestroy) {
        TimedMockTask *task1 = new TimedMockTask(2);
        TimedMockTask *task2 = new TimedMockTask(3);
        TimedMockTask *task3 = new TimedMockTask(4);
        TimedMockTask *task4 = new TimedMockTask(5);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->destroy());
    }
}
