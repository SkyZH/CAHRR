//
// Created by Alex Chi on 2018/11/11.
//

#include "SequentialTask.h"

class SequentialEndTask : public Task {
private:
    SequentialTask* task;
    bool do_reset;
    bool cycle;
public:
    SequentialEndTask(SequentialTask* task, bool cycle) : Task(), task(task), cycle(cycle) {
        this->do_reset = false;
    }

    bool isEnd() { return false || (this->do_reset && !this->cycle); }

    bool initialize() {
        this->do_reset = true;
        return true;
    }
    bool update() {
        this->do_reset = true;
        if (this->cycle) {
            task->destroy();
            task->initialize();
            this->do_reset = false;
            return task->update();
        }
        return true;
    }

    bool destroy() {
        this->do_reset = false;
        return true;
    }
};

bool SequentialTask::initialize() {
    return this->mainTask->initialize();
}

bool SequentialTask::destroy() {
    return this->mainTask->destroy();
}

bool SequentialTask::update() {
    return this->mainTask->update();
}

SequentialTask::SequentialTask(const std::vector<Task *> &tasks, bool cycle) : Task() {
    std::vector<Task*>::const_reverse_iterator iter = tasks.rbegin();
    this->endTask = new SequentialEndTask(this, cycle);
    this->mainTask = new AutoSwitchTask(*(iter++), this->endTask);
    for(; iter != tasks.rend(); iter++) {
        this->mainTask = new AutoSwitchTask(*iter, this->mainTask);
    }
}

bool SequentialTask::isEnd() {
    return this->endTask->isEnd();
}

SequentialTask::~SequentialTask() {
    // TODO: delete all tasks
    delete this->endTask;
    delete this->mainTask;
}

