//
// Created by Alex Chi on 2018/11/12.
//

#ifndef CAHRR_PARALLELTASK_H
#define CAHRR_PARALLELTASK_H

#include <vector>
#include "Task.h"

class ParallelTask : public Task {
    const std::vector <Task*> tasks;
public:
    ParallelTask(const std::vector <Task*> &tasks);

    virtual bool initialize();

    virtual bool destroy();

    virtual bool isEnd();

    virtual bool update();
};


#endif //CAHRR_PARALLELTASK_H
