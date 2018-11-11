//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_TRIGGERSWITCHTASK_H
#define CAHRR_TRIGGERSWITCHTASK_H

#include "SwitchTask.h"

class TriggerSwitchTask : public SwitchTask  {
private:
    bool lst_triggered;
public:
    TriggerSwitchTask(Task *task1, Task *task2);

    virtual bool initialize();

    virtual bool update();

    virtual bool trigger() = 0;
};


#endif //CAHRR_TRIGGERSWITCHTASK_H
