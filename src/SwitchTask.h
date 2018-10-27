//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_SWITCHTASK_H
#define CAHRR_SWITCHTASK_H

#include "Task.h"

class SwitchTask : public Task {
private:
    Task* task1;
    Task* task2;
public:
    SwitchTask(Task* task1, Task* task2);
    bool select(bool task);
    bool initialize(bool initial_status);
    bool initialize();
    bool destroy();
    bool update();
    bool selected;
};


#endif //CAHRR_SWITCHTASK_H
