//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_CANSYSTEM_H
#define CAHRR_CANSYSTEM_H

class CANSystem {
public:
    CANSystem() = default;

    virtual bool initialize() = 0;

    virtual bool destroy() = 0;

    virtual bool update() = 0;

    virtual bool set(int id, uint16_t data) = 0;

    virtual uint16_t get(int id, int data_id) = 0;
};

#endif //CAHRR_CANSYSTEM_H
