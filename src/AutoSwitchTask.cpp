//
// Created by Alex Chi on 2018/11/11.
//

#include "AutoSwitchTask.h"

AutoSwitchTask::AutoSwitchTask(Task *task1, Task *task2) : SwitchTask(task1, task2) {
}

bool AutoSwitchTask::update() {
    if (this->isEnd()) {
        return false;
    } else {
        this->select(this->do_select(this->selected));
        return SwitchTask::update();
    }
}

bool AutoSwitchTask::isEnd() {
    return (this->task1 && this->task1->isEnd() || !this->task1) && (this->task2 && this->task2->isEnd() || !this->task2);
}

bool AutoSwitchTask::do_select(bool try_select) {
    bool selected = try_select;
    if (!selected) {
        if (this->task1) {
            if (task1->isEnd()) {
                selected = true;
            }
        } else {
            selected = true;
        }
    } else {
        if (this->task2) {
            if (task2->isEnd()) {
                selected = false;
            }
        } else {
            selected = false;
        }
    }
    return selected;
}

bool AutoSwitchTask::initialize() {
    return SwitchTask::initialize(this->do_select(false));
}

