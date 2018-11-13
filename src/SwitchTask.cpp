//
// Created by Alex Chi on 2018/10/26.
//

#include "SwitchTask.h"

SwitchTask::SwitchTask(Task *task1, Task *task2) : task1(task1), task2(task2), selected(false) {

}

bool SwitchTask::select(bool task) {
    if (this->selected == task) {
        return true;
    } else {
        this->selected = task;
        if (!task) {
            if (!this->destroy_task(task2)) return false;
            return this->initialize_task(task1);
        } else {
            if (!this->destroy_task(task1)) return false;
            return this->initialize_task(task2);
        }
    }
}

bool SwitchTask::initialize(bool initial_status) {
    this->selected = initial_status;
    if (!this->selected) {
        return this->initialize_task(task1);
    } else {
        return this->initialize_task(task2);
    }
}

bool SwitchTask::destroy() {
    if (!this->selected) {
        return this->destroy_task(task1);
    } else {
        return this->destroy_task(task2);
    }
}

bool SwitchTask::update() {
    if (!this->selected) {
        return this->update_task(task1);
    } else {
        return this->update_task(task2);
    }
}

bool SwitchTask::initialize() {
    return this->initialize(false);
}

bool SwitchTask::destroy_task(Task *task) {
    if (!task) return true;
    return task->destroy();
}

bool SwitchTask::initialize_task(Task *task) {
    if (!task) return true;
    return task->initialize();
}

bool SwitchTask::update_task(Task *task) {
    if (!task) return true;
    return task->update();
}
