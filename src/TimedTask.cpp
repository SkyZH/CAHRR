//
// Created by Alex Chi on 2018/11/11.
//

#include "TimedTask.h"

bool TimedTask::initialize() {
    this->_timed_initialized = true;
    this->_timed_start_time = this->time();
    return true;
}

bool TimedTask::destroy() {
    this->_timed_initialized = false;
    return true;
}

bool TimedTask::isEnd() {
    if (!this->_timed_initialized) return false;
    return this->time() - this->_timed_start_time >= this->total_time;
}

TimedTask::TimedTask(unsigned int total_time)
        : Task(), total_time(total_time), _timed_initialized(false), _timed_start_time(0) {
}
