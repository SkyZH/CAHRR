//
// Created by Alex Chi on 2018/11/13.
//

#ifndef CAHRR_MOCKULTRASONICSYSTEM_H
#define CAHRR_MOCKULTRASONICSYSTEM_H

#define uint16_t unsigned int

#include "../src/UltrasonicSystem.h"

class MockUltrasonicSystem : public UltrasonicSystem {
private:
    uint16_t lst_sent;
    uint16_t delta_time;
    bool data_available;
    void send_data();
    uint16_t available_time;
public:
    MockUltrasonicSystem();

    virtual bool trigger();

    virtual bool initialize();

    virtual bool update();

    virtual bool destroy();

    virtual double distance();

    virtual uint16_t time();
};


#endif //CAHRR_MOCKULTRASONICSYSTEM_H
