//
// Created by Alex Chi on 2018/10/26.
//

#include "MockChassisSystem.h"

double chassis_sent_data_bf, chassis_sent_data_lr;

MockChassisSystem::MockChassisSystem() {
    this->initialized = false;
}

bool MockChassisSystem::initialize() {
    if (this->initialized) return false;
    this->initialized = true;
    return true;
}

bool MockChassisSystem::update() {
    chassis_sent_data_lr = this->LeftRight;
    chassis_sent_data_bf = this->BackForward;
    return true;
}

bool MockChassisSystem::destroy() {
    if (!this->initialized) return false;
    this->initialized = false;
    chassis_sent_data_bf = 0;
    chassis_sent_data_lr = 0;
    return true;
}

bool MockChassisSystem::data() {
    return true;
}

bool MockChassisSystem::setSpeed(double bf, double lr) {
    this->BackForward = bf;
    this->LeftRight = lr;
    return true;
}
