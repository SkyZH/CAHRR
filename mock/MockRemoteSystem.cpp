//
// Created by Alex Chi on 2018/10/28.
//

#include <cstdint>
#include "MockRemoteSystem.h"
#include "../src/RemoteSystem.h"

int remote_axis_test = 0;

MockRemoteSystem::MockRemoteSystem() : axis_data(0) {
}

bool MockRemoteSystem::initialize() {
    remote_axis_test = 0;
    return true;
}

bool MockRemoteSystem::destroy() {
    return true;
}

int16_t MockRemoteSystem::getAxis(int id) {
    return this->axis_data;
}

int16_t MockRemoteSystem::getButton(int id) {
    return 1;
}

bool MockRemoteSystem::data() {
    this->axis_data = remote_axis_test;
    return true;
}
