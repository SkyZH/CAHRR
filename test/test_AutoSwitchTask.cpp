//
// Created by Alex Chi on 2018/11/10.
//

#include "gtest/gtest.h"
#include "AutoSwitchTask.h"
#include "MockTask.h"

namespace {
    int selected_task = 0;

    class AutoSwitchTaskTest : public ::testing::Test {
    protected:

        AutoSwitchTaskTest() {
        }

        ~AutoSwitchTaskTest() override {
        }

        void SetUp() override {
            selected_task = 0;
        }

        void TearDown() override {
            selected_task = -1;
        }
    };

    class MockTask0 : public MockTask {
    public:
        MockTask0() : MockTask() {
        }

        virtual bool isEnd() {
            return selected_task != 0;
        }
    };
    class MockTask1 : public MockTask {
    public:
        MockTask1() : MockTask() {
        }

        virtual bool isEnd() {
            return selected_task != 1;
        }
    };
    class MockTask2 : public MockTask {
    public:
        MockTask2() : MockTask() {
        }

        virtual bool isEnd() {
            return selected_task != 2;
        }
    };
    class MockTask3 : public MockTask {
    public:
        MockTask3() : MockTask() {
        }

        virtual bool isEnd() {
            return selected_task != 3;
        }
    };

    TEST_F(AutoSwitchTaskTest, TestInitialize) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask0, mockTask1);
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
    }

    TEST_F(AutoSwitchTaskTest, TestInitializeReverse) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask1, mockTask0);
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
    }

    TEST_F(AutoSwitchTaskTest, TestInitialize2) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask1, mockTask0);
        selected_task = 1;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_EQ(mockTask0->initialize_count, 0);
        EXPECT_EQ(mockTask1->initialize_count, 1);
    }

    TEST_F(AutoSwitchTaskTest, TestInitialize2Reverse) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask0, mockTask1);
        selected_task = 1;
        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_EQ(mockTask0->initialize_count, 0);
        EXPECT_EQ(mockTask1->initialize_count, 1);
    }

    TEST_F(AutoSwitchTaskTest, TestIsEnd) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask1, mockTask0);
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_FALSE(task->isEnd());
        EXPECT_TRUE(task->update());
        EXPECT_FALSE(task->isEnd());
    }

    TEST_F(AutoSwitchTaskTest, TestUpdate) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        MockTask *mockTask2 = new MockTask2;
        MockTask *mockTask3 = new MockTask3;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask0, new AutoSwitchTask(mockTask1, new AutoSwitchTask(mockTask2, mockTask3)));
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_EQ(mockTask0->initialize_count, 1);
        EXPECT_EQ(mockTask0->destroy_count, 0);
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_EQ(mockTask1->initialize_count, 0);
        EXPECT_EQ(mockTask1->destroy_count, 0);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->initialize_count, 0);
        EXPECT_EQ(mockTask2->destroy_count, 0);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->initialize_count, 0);
        EXPECT_EQ(mockTask3->destroy_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask3->initialized);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->update_count, 1);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->initialize_count, 1);
        EXPECT_EQ(mockTask0->destroy_count, 1);
        EXPECT_EQ(mockTask1->initialize_count, 1);
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_EQ(mockTask1->update_count, 1);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->update_count, 1);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 1);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 2);


        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 3);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 0;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask0->initialized);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask1->initialized);
    }

    void update_test_sequence(MockTask* mockTask0, MockTask* mockTask1, MockTask* mockTask2, MockTask* mockTask3, AutoSwitchTask* task) {
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask3->initialized);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->update_count, 1);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_EQ(mockTask1->update_count, 1);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->update_count, 1);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->update_count, 1);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->update_count, 2);


        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->update_count, 3);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 0;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask0->initialized);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask1->initialized);

        EXPECT_TRUE(task->destroy());
    }

    TEST_F(AutoSwitchTaskTest, TestUpdate2) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        MockTask *mockTask2 = new MockTask2;
        MockTask *mockTask3 = new MockTask3;
        AutoSwitchTask *task = new AutoSwitchTask(new AutoSwitchTask(mockTask0, mockTask1), new AutoSwitchTask(mockTask2, mockTask3));
        selected_task = 0;
        EXPECT_TRUE(task->initialize());
        EXPECT_EQ(mockTask0->initialize_count, 1);
        EXPECT_EQ(mockTask0->destroy_count, 0);
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_EQ(mockTask1->initialize_count, 0);
        EXPECT_EQ(mockTask1->destroy_count, 0);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->initialize_count, 0);
        EXPECT_EQ(mockTask2->destroy_count, 0);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->initialize_count, 0);
        EXPECT_EQ(mockTask3->destroy_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask3->initialized);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->update_count, 1);
        EXPECT_EQ(mockTask1->update_count, 0);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask0->initialize_count, 1);
        EXPECT_EQ(mockTask0->destroy_count, 1);
        EXPECT_EQ(mockTask1->initialize_count, 1);
        EXPECT_EQ(mockTask0->update_count, 0);
        EXPECT_EQ(mockTask1->update_count, 1);
        EXPECT_EQ(mockTask2->update_count, 0);
        EXPECT_EQ(mockTask3->update_count, 0);
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask2->update_count, 1);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 1);

        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 2);


        EXPECT_TRUE(task->update());
        EXPECT_EQ(mockTask3->initialize_count, 1);
        EXPECT_EQ(mockTask3->update_count, 3);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 0;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);

        selected_task = 2;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask2->initialized);
        EXPECT_FALSE(mockTask0->initialized);

        selected_task = 1;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);

        selected_task = 3;
        EXPECT_TRUE(task->update());
        EXPECT_TRUE(mockTask3->initialized);
        EXPECT_FALSE(mockTask1->initialized);
    }

    TEST_F(AutoSwitchTaskTest, TestUpdate2Multi) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        MockTask *mockTask2 = new MockTask2;
        MockTask *mockTask3 = new MockTask3;
        AutoSwitchTask *task = new AutoSwitchTask(new AutoSwitchTask(mockTask0, mockTask1), new AutoSwitchTask(mockTask2, mockTask3));
        update_test_sequence(mockTask0, mockTask1, mockTask2, mockTask3, task);
        update_test_sequence(mockTask0, mockTask1, mockTask2, mockTask3, task);
        update_test_sequence(mockTask0, mockTask1, mockTask2, mockTask3, task);
    }


    TEST_F(AutoSwitchTaskTest, TestDestroy) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask1;
        MockTask *mockTask2 = new MockTask2;
        MockTask *mockTask3 = new MockTask3;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask0, new AutoSwitchTask(mockTask1, new AutoSwitchTask(mockTask2, mockTask3)));
        selected_task = 0;

        EXPECT_TRUE(task->initialize());

        EXPECT_TRUE(task->update());

        selected_task = 1;
        EXPECT_TRUE(task->update());

        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_FALSE(mockTask2->initialized);
        EXPECT_FALSE(mockTask3->initialized);
    }


    TEST_F(AutoSwitchTaskTest, TestNull) {
        AutoSwitchTask *task = new AutoSwitchTask(nullptr, nullptr);
        selected_task = 0;

        EXPECT_TRUE(task->initialize());

        EXPECT_FALSE(task->update());

        EXPECT_FALSE(task->update());

        EXPECT_TRUE(task->destroy());
    }

    TEST_F(AutoSwitchTaskTest, TestPriority) {
        MockTask *mockTask0 = new MockTask0;
        MockTask *mockTask1 = new MockTask0;
        AutoSwitchTask *task = new AutoSwitchTask(mockTask0, mockTask1);
        selected_task = 0;

        EXPECT_TRUE(task->initialize());
        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);

        EXPECT_TRUE(task->update());

        EXPECT_TRUE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
        EXPECT_EQ(mockTask0->update_count, 1);
        EXPECT_EQ(mockTask1->update_count, 0);

        EXPECT_TRUE(task->destroy());
        EXPECT_FALSE(mockTask0->initialized);
        EXPECT_FALSE(mockTask1->initialized);
    }
}

