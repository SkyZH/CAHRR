//
// Created by Alex Chi on 2018/10/27.
//

#include "MockIMUSystem.h"

int imu_data[100];

bool MockIMUSystem::initialize() {
    return true;
}

bool MockIMUSystem::destroy() {
    return true;
}

bool MockIMUSystem::update() {
    for (int i = 0; i < 10; i++) this->IMUData[i] = imu_data[i];
    return true;
}

uint16_t MockIMUSystem::get(int data) {
    return this->IMUData[data];
}
