//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_AUTOSWITCHTASK_H
#define CAHRR_AUTOSWITCHTASK_H

#include "SwitchTask.h"

class AutoSwitchTask : public SwitchTask {
private:
    bool do_select(bool try_select);
public:
    AutoSwitchTask(Task *task1, Task *task2);

    virtual bool initialize();

    virtual bool update();

    virtual bool isEnd();
};


#endif //CAHRR_AUTOSWITCHTASK_H
