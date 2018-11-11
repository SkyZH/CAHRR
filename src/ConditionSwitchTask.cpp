//
// Created by Alex Chi on 2018/11/11.
//

#include "ConditionSwitchTask.h"

bool ConditionSwitchTask::initialize() {
    return SwitchTask::initialize(this->when());
}

bool ConditionSwitchTask::update() {
    this->select(this->when());
    return SwitchTask::update();
}

ConditionSwitchTask::ConditionSwitchTask(Task *task1, Task *task2) : SwitchTask(task1, task2) {

}
