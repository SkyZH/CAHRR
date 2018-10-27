//
// Created by Alex Chi on 2018/10/26.
//

#include "SwitchTask.h"

SwitchTask::SwitchTask(Task *task1, Task *task2)  : task1(task1), task2(task2) {

}

bool SwitchTask::select(bool task) {
    if (this->selected == task) {
        return true;
    } else {
        this->selected = task;
        if (!task) {
            if (!this->task2->destroy()) return false;
            return this->task1->initialize();
        } else {
            if (!this->task1->destroy()) return false;
            return this->task2->initialize();
        }
    }
}

bool SwitchTask::initialize(bool initial_status) {
    this->selected = initial_status;
    if (!this->selected) {
        return this->task1->initialize();
    } else {
        return this->task2->initialize();
    }
}

bool SwitchTask::destroy() {
    if (!this->selected) {
        return this->task1->destroy();
    } else {
        return this->task2->destroy();
    }
}

bool SwitchTask::update() {
    if (!this->selected) {
        return this->task1->update();
    } else {
        return this->task2->update();
    }
}

bool SwitchTask::initialize() {
    return this->initialize(false);
}
