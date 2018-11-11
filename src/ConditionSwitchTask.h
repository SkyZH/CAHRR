//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_CONDITIONSWITCHTASK_H
#define CAHRR_CONDITIONSWITCHTASK_H

#include "SwitchTask.h"

class ConditionSwitchTask : public SwitchTask {
public:
    ConditionSwitchTask(Task *task1, Task *task2);

    virtual bool initialize();

    virtual bool update();

    virtual bool when() = 0;
};


#endif //CAHRR_CONDITIONSWITCHTASK_H
