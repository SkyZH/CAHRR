//
// Created by Alex Chi on 2018/10/28.
//

#include "gtest/gtest.h"
#include "mock/MockRemoteSystem.h"
#include <string>

namespace {
    TEST(RemoteSystemTest, TestInitialize) {
        MockRemoteSystem *remoteSystem = new MockRemoteSystem;
        remote_axis_test = 233;
        EXPECT_TRUE(remoteSystem->initialize());
        EXPECT_EQ(remote_axis_test, 0);
    }
    TEST(RemoteSystemTest, TestDestroy) {
        MockRemoteSystem *remoteSystem = new MockRemoteSystem;
        EXPECT_TRUE(remoteSystem->initialize());
        EXPECT_TRUE(remoteSystem->destroy());
    }
    TEST(RemoteSystemTest, TestFeedData) {
        MockRemoteSystem *remoteSystem = new MockRemoteSystem;
        EXPECT_TRUE(remoteSystem->initialize());
        EXPECT_TRUE(remoteSystem->data());
    }
    TEST(RemoteSystemTest, TestGetAxisData) {
        MockRemoteSystem *remoteSystem = new MockRemoteSystem;
        EXPECT_TRUE(remoteSystem->initialize());
        remote_axis_test = 233;
        EXPECT_TRUE(remoteSystem->data());
        EXPECT_EQ(remoteSystem->getAxis(0), 233);
        EXPECT_EQ(remoteSystem->getButton(0), 1);
    }
}

