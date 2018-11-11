//
// Created by Alex Chi on 2018/11/11.
//

#include "TimedTask.h"

bool TimedTask::initialize() {
    this->initialized = true;
    this->start_time = this->time();
    return true;
}

bool TimedTask::destroy() {
    this->initialized = false;
    return true;
}

bool TimedTask::isEnd() {
    if (!this->initialized) return false;
    return this->time() - this->start_time >= this->total_time;
}

TimedTask::TimedTask(unsigned int total_time) : Task(), total_time(total_time) {
}
