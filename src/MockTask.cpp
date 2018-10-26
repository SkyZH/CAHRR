//
// Created by Alex Chi on 2018/10/26.
//

#include "MockTask.h"

MockTask::MockTask() {
    this->initialized = false;
    this->initialize_count = this->destroy_count = 0;
    this->update_count = 0;
}

bool MockTask::initialize() {
    this->initialized = true;
    this->update_count = 0;
    this->initialize_count++;
    return true;
}

bool MockTask::destroy() {
    this->initialized = false;
    this->destroy_count++;
    this->update_count = 0;
    return true;
}

bool MockTask::update() {
    this->update_count++;
    return true;
}
