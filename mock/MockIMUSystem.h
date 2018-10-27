//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_MOCKIMUSYSTEM_H
#define CAHRR_MOCKIMUSYSTEM_H

#define uint16_t int

#include "../src/IMUSystem.h"

extern int imu_data[100];

class MockIMUSystem : public IMUSystem {
private:
    int IMUData[100] = { 0 };
public:
    MockIMUSystem() = default;

    bool initialize();

    bool destroy();

    bool update();

    uint16_t get(int data);
};


#endif //CAHRR_MOCKIMUSYSTEM_H
