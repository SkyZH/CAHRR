//
// Created by Alex Chi on 2018/10/27.
//

#include "MockCANSystem.h"

int can_sent_data[1000];
int can_received_data[1000];

MockCANSystem::MockCANSystem() {
}

bool MockCANSystem::initialize() {
    return true;
}

bool MockCANSystem::destroy() {
    return true;
}

bool MockCANSystem::update() {
    for (int i = 0; i < 10; i++) can_sent_data[i] = this->canData[i];
    return true;
}

bool MockCANSystem::set(int id, uint16_t data) {
    this->canData[id] = data;
    return true;
}

bool MockCANSystem::data() {
    for (int i = 0; i < 10; i++) this->canRecv[i] = can_received_data[i];
    return true;
}

int MockCANSystem::get(int id, int data_id) {
    return this->canRecv[id + data_id];
}
