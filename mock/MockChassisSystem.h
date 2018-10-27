//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_MOCKCHASSISSYSTEM_H
#define CAHRR_MOCKCHASSISSYSTEM_H

#include "../src/ChassisSystem.h"

extern double chassis_sent_data_bf, chassis_sent_data_lr;

class MockChassisSystem : public ChassisSystem {
private:
    bool initialized;
public:
    MockChassisSystem();

    bool initialize();

    bool update();

    bool destroy();

    bool data();

    bool setSpeed(double bf, double lr);

    int BackForward, LeftRight;
};

#endif //CAHRR_MOCKCHASSISSYSTEM_H
