//
// Created by Alex Chi on 2018/10/27.
//

#include "MockIMUSystem.h"

bool MockIMUSystem::initialize() {
    return false;
}

bool MockIMUSystem::destroy() {
    return false;
}

bool MockIMUSystem::update() {
    return false;
}

uint16_t MockIMUSystem::get(int data) {
    return 0;
}
