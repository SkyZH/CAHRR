//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_MOCKTASK_H
#define CAHRR_MOCKTASK_H

#include "Task.h"

class MockTask : public Task {
public:
    MockTask();
    bool initialize();
    bool destroy();
    bool update();
    bool initialized;
    int update_count, initialize_count, destroy_count;
};


#endif //CAHRR_MOCKTASK_H
