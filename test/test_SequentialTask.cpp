//
// Created by Alex Chi on 2018/11/11.
//

#include "gtest/gtest.h"
#include "MockTask.h"
#include "SequentialTask.h"
#include <vector>

namespace {
    class SequentialTaskTest : public ::testing::Test {
    protected:
        SequentialTaskTest() {
        }

        ~SequentialTaskTest() override {
        }

        void SetUp() override {
        }
    };

    class MockCompletableTask : public MockTask {
        bool is_end = false;
    public:
        virtual bool destroy() {
            this->is_end = false;
            return MockTask::destroy();
        }

        virtual bool isEnd() {
            return is_end;
        }

        void complete() { this->is_end = true; }
        void ready() { this->is_end = false; }
    };


    TEST_F(SequentialTaskTest, TestInitialize) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
    }

    TEST_F(SequentialTaskTest, TestUpdate) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
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

        task1->complete();
        EXPECT_TRUE(task1->isEnd());
        EXPECT_FALSE(task2->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->isEnd());
        EXPECT_FALSE(task2->isEnd());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->initialize_count, 1);
        EXPECT_EQ(task1->initialize_count, 1);
        EXPECT_EQ(task2->update_count, 1);

        task2->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);

        task3->complete();
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        EXPECT_EQ(task4->update_count, 1);

        task4->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task1->update_count, 2);
    }

    void test_sequence_update(MockCompletableTask* task1, MockCompletableTask* task2, MockCompletableTask* task3, MockCompletableTask* task4, SequentialTask* task) {
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_FALSE(task->isEnd());

        task1->complete();
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->update_count, 1);
        EXPECT_FALSE(task->isEnd());

        task2->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);
        EXPECT_FALSE(task->isEnd());

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 4);
        EXPECT_FALSE(task->isEnd());

        task3->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        EXPECT_EQ(task4->update_count, 3);
        EXPECT_FALSE(task->isEnd());

        task4->complete();
    }

    void test_sequence_update_complete(MockCompletableTask* task1, MockCompletableTask* task2, MockCompletableTask* task3, MockCompletableTask* task4, SequentialTask* task) {
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        task4->ready();
        EXPECT_EQ(task1->update_count, 1);
        EXPECT_FALSE(task->isEnd());

        task1->complete();
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->update_count, 1);
        task1->ready();
        EXPECT_FALSE(task->isEnd());

        task2->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);
        task2->ready();
        EXPECT_FALSE(task->isEnd());

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 4);
        EXPECT_FALSE(task->isEnd());

        task3->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        EXPECT_EQ(task4->update_count, 3);
        task3->ready();
        EXPECT_FALSE(task->isEnd());

        task4->complete();
    }

    TEST_F(SequentialTaskTest, TestUpdateMulti) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
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
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }), false);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        test_sequence_update(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestCompleteUpdateMulti) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        test_sequence_update_complete(task1, task2, task3, task4, task);
        test_sequence_update_complete(task1, task2, task3, task4, task);
        test_sequence_update_complete(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestCompleteUpdateNoCycle) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }), false);
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        test_sequence_update_complete(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestCompleteUpdateWithInterrupt) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
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
        task1->complete();
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->update_count, 1);
        task1->ready();
        EXPECT_FALSE(task->isEnd());

        task2->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);
        task2->ready();
        EXPECT_FALSE(task->isEnd());

        ASSERT_TRUE(task->destroy());
        ASSERT_TRUE(task->initialize());
        test_sequence_update_complete(task1, task2, task3, task4, task);
        test_sequence_update_complete(task1, task2, task3, task4, task);
        test_sequence_update_complete(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestCompleteUpdateNoCycleWithInterrupt) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }), false);
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
        task1->complete();
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task2->update_count, 1);
        task1->ready();
        EXPECT_FALSE(task->isEnd());

        task2->complete();
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_EQ(task3->update_count, 2);
        task2->ready();
        EXPECT_FALSE(task->isEnd());

        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->update());

        ASSERT_TRUE(task->destroy());
        ASSERT_TRUE(task->initialize());
        test_sequence_update(task1, task2, task3, task4, task);
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestDestroy) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ task1, task2, task3, task4 }));
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestSequenceInSequence) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *taskS1 = new SequentialTask(std::vector <Task*> ({ task1, task2 }), false);
        SequentialTask *taskS2 = new SequentialTask(std::vector <Task*> ({ task3, task4 }), false);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ taskS1, taskS2 }), false);
        ASSERT_TRUE(task->initialize());
        ASSERT_TRUE(task->update());
        EXPECT_TRUE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        task1->complete();

        ASSERT_TRUE(task->update());
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_TRUE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        task2->complete();
        EXPECT_FALSE(task->isEnd());
        task1->ready();
        ASSERT_TRUE(task->update());
        task2->ready();
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_TRUE(task3->initialized);
        EXPECT_FALSE(task4->initialized);
        EXPECT_FALSE(task->isEnd());
        task3->complete();
        ASSERT_TRUE(task->update());
        ASSERT_TRUE(task->update());
        EXPECT_FALSE(task1->initialized);
        EXPECT_FALSE(task2->initialized);
        EXPECT_FALSE(task3->initialized);
        EXPECT_TRUE(task4->initialized);
        task3->ready();
        EXPECT_FALSE(task->isEnd());

        task4->complete();
        ASSERT_TRUE(task->update());


        ASSERT_TRUE(task->update());
        EXPECT_TRUE(task->isEnd());

        ASSERT_TRUE(task->destroy());
    }

    TEST_F(SequentialTaskTest, TestSequenceInSequenceCycle) {
        MockCompletableTask *task1 = new MockCompletableTask;
        MockCompletableTask *task2 = new MockCompletableTask;
        MockCompletableTask *task3 = new MockCompletableTask;
        MockCompletableTask *task4 = new MockCompletableTask;
        SequentialTask *taskS1 = new SequentialTask(std::vector <Task*> ({ task1, task2 }), false);
        SequentialTask *taskS2 = new SequentialTask(std::vector <Task*> ({ task3, task4 }), false);
        SequentialTask *task = new SequentialTask(std::vector <Task*> ({ taskS1, taskS2 }), true);
        ASSERT_TRUE(task->initialize());

        for (int i = 0; i < 10; i++) {

            ASSERT_TRUE(task->update());
            EXPECT_TRUE(task1->initialized);
            EXPECT_FALSE(task2->initialized);
            EXPECT_FALSE(task3->initialized);
            EXPECT_FALSE(task4->initialized);
            task1->complete();

            ASSERT_TRUE(task->update());
            ASSERT_TRUE(task->update());
            EXPECT_FALSE(task1->initialized);
            EXPECT_TRUE(task2->initialized);
            EXPECT_FALSE(task3->initialized);
            EXPECT_FALSE(task4->initialized);
            task2->complete();
            EXPECT_FALSE(task->isEnd());
            task1->ready();
            ASSERT_TRUE(task->update());
            task2->ready();
            ASSERT_TRUE(task->update());
            EXPECT_FALSE(task->isEnd());
            EXPECT_FALSE(task1->initialized);
            EXPECT_FALSE(task2->initialized);
            EXPECT_TRUE(task3->initialized);
            EXPECT_FALSE(task4->initialized);
            EXPECT_FALSE(task->isEnd());
            task3->complete();
            ASSERT_TRUE(task->update());
            ASSERT_TRUE(task->update());
            EXPECT_FALSE(task1->initialized);
            EXPECT_FALSE(task2->initialized);
            EXPECT_FALSE(task3->initialized);
            EXPECT_TRUE(task4->initialized);
            task3->ready();
            EXPECT_FALSE(task->isEnd());

            task4->complete();
            ASSERT_TRUE(task->update());


            ASSERT_TRUE(task->update());
            EXPECT_FALSE(task->isEnd());
        }

        ASSERT_TRUE(task->destroy());
    }
}
