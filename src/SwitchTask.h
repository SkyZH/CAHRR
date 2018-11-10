//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_SWITCHTASK_H
#define CAHRR_SWITCHTASK_H

#include "Task.h"

class SwitchTask : public Task {
protected:
    Task *task1;
    Task *task2;

private:
    bool initialize_task(Task *task);

    bool destroy_task(Task *task);

    bool update_task(Task *task);

public:
    SwitchTask(Task *task1, Task *task2);

    virtual bool select(bool task);

    virtual bool initialize(bool initial_status);

    virtual bool initialize();

    virtual bool destroy();

    virtual bool update();

    bool selected;
};


#endif //CAHRR_SWITCHTASK_H
