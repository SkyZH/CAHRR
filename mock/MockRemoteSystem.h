//
// Created by Alex Chi on 2018/10/28.
//

#ifndef CAHRR_MOCKREMOTESYSTEM_H
#define CAHRR_MOCKREMOTESYSTEM_H

#define int16_t int

#include "../src/RemoteSystem.h"

extern int remote_axis_test;

class MockRemoteSystem : public RemoteSystem {
private:
    int axis_data;
public:
    MockRemoteSystem();

    bool initialize();

    bool destroy();

    int16_t getAxis(int id);

    int16_t getButton(int id);

    bool data();
};


#endif //CAHRR_MOCKREMOTESYSTEM_H
