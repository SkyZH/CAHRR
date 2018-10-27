//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_MOCKCANSYSTEM_H
#define CAHRR_MOCKCANSYSTEM_H

#define uint16_t int

#include "../src/CANSystem.h"

extern int can_sent_data[];
extern int can_received_data[];

class MockCANSystem : public CANSystem {
private:
    int canData[1000] = {0};
    int canRecv[1000] = {0};
public:
    MockCANSystem();


    bool initialize();

    bool destroy();

    bool update();

    bool set(int id, uint16_t data);

    int get(int id, int data_id);

    bool data();
};


#endif //CAHRR_MOCKCANSYSTEM_H
