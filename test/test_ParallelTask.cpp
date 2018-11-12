//
// Created by Alex Chi on 2018/11/12.
//

#include "gtest/gtest.h"
#include "ParallelTask.h"
#include "MockTask.h"

namespace {
    class MockEndTask : public MockTask {
    public:
        MockEndTask() : MockTask() {

        }

        virtual bool isEnd() {
            return true;
        }
    };
    TEST(ParallelTaskTest, TestInitialize) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTask* task2 = new MockTask;
        ParallelTask *task = new ParallelTask(std::vector<Task*>({ task0, task1, task2 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task0->initialized);
        EXPECT_TRUE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
    }
    TEST(ParallelTaskTest, TestDestroy) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTask* task2 = new MockTask;
        ParallelTask *task = new ParallelTask(std::vector<Task*>({ task0, task1, task2 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(task0->initialized);
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
    }
    TEST(ParallelTaskTest, TestUpdate) {
        MockTask* task0 = new MockTask;
        MockTask* task1 = new MockTask;
        MockTask* task2 = new MockTask;
        ParallelTask *task = new ParallelTask(std::vector<Task*>({ task0, task1, task2 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->update());
        EXPECT_EQ(task0->update_count, 1);
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_EQ(task2->update_count, 1);
    }
    TEST(ParallelTaskTest, TestIsEnd) {
        MockTask* task0 = new MockEndTask;
        MockTask* task1 = new MockEndTask;
        MockTask* task2 = new MockEndTask;
        ParallelTask *task = new ParallelTask(std::vector<Task*>({ task0, task1, task2 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->isEnd());
    }
    TEST(ParallelTaskTest, TestIsNotEnd) {
        MockTask* task0 = new MockEndTask;
        MockTask* task1 = new MockEndTask;
        MockTask* task2 = new MockTask;
        ParallelTask *task = new ParallelTask(std::vector<Task*>({ task0, task1, task2 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
    }
}
