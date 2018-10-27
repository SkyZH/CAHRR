//
// Created by Alex Chi on 2018/10/26.
//

#include "ChassisSystem.h"

int chassis_sent_data_bf, chassis_sent_data_lr;

ChassisSystem::ChassisSystem() {
    this->initialized = false;
}

bool ChassisSystem::initialize() {
    if (this->initialized) return false;
    this->initialized = true;
    return true;
}

bool ChassisSystem::update() {
    chassis_sent_data_lr = this->LeftRight;
    chassis_sent_data_bf = this->BackForward;
    return true;
}

bool ChassisSystem::destroy() {
    if (!this->initialized) return false;
    this->initialized = false;
    chassis_sent_data_bf = 0;
    chassis_sent_data_lr = 0;
    return true;
}

bool ChassisSystem::data() {
    return true;
}

bool ChassisSystem::setSpeed(int bf, int lr) {
    this->BackForward = bf;
    this->LeftRight = lr;
    return true;
}
