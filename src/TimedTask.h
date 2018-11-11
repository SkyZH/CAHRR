//
// Created by Alex Chi on 2018/11/11.
//

#ifndef CAHRR_TIMEDTASK_H
#define CAHRR_TIMEDTASK_H

#include "Task.h"

class TimedTask : public Task {
private:
    bool initialized;
    unsigned int total_time;
    unsigned int start_time;
public:
    TimedTask(unsigned int total_time);

    virtual bool initialize();

    virtual bool destroy();

    virtual bool isEnd();

    virtual unsigned int time() = 0;
};


#endif //CAHRR_TIMEDTASK_H
