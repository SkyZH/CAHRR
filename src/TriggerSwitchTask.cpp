//
// Created by Alex Chi on 2018/11/11.
//

#include "TriggerSwitchTask.h"

TriggerSwitchTask::TriggerSwitchTask(Task *task1, Task *task2) : SwitchTask(task1, task2) {

}

bool TriggerSwitchTask::initialize() {
    this->lst_triggered = false;
    return SwitchTask::initialize(false);
}

bool TriggerSwitchTask::update() {
    bool _t = this->trigger();
    if (this->lst_triggered != _t) {
        this->lst_triggered = _t;
        if (_t) {
            this->select(!this->selected);
        }
    }
    return SwitchTask::update();
}
