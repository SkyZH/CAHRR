//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_AUTOTASK_H
#define CAHRR_AUTOTASK_H

#include "Task.h"
class AutoTask : public Task {
public:
    virtual bool isEnd() { return false; }
};


#endif //CAHRR_AUTOTASK_H
