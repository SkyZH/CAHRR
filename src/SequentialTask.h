//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_SEQUENTIALTASK_H
#define CAHRR_SEQUENTIALTASK_H


#include "Task.h"
#include "AutoSwitchTask.h"
#include <vector>

class SequentialTask : public Task {
private:
    AutoSwitchTask* mainTask;
    Task* endTask;
public:
    SequentialTask(const std::vector <Task*> &tasks, bool cycle = true);

    virtual bool initialize();

    virtual bool destroy();

    virtual bool update();

    virtual bool isEnd();

    virtual ~SequentialTask();
};


#endif //CAHRR_SEQUENTIALTASK_H
