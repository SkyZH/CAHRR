//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_MOCKCANSYSTEM_H
#define CAHRR_MOCKCANSYSTEM_H

#define uint16_t int

#include "../src/CANSystem.h"

extern int can_sent_data[300];

class MockCANSystem : public CANSystem {
public:
    MockCANSystem();

    bool initialize();
    bool destroy();
    bool update();
    bool set(int id, uint16_t data);
    bool data();
};


#endif //CAHRR_MOCKCANSYSTEM_H
