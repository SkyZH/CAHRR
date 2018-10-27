//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_IMUSYSTEM_H
#define CAHRR_IMUSYSTEM_H

class IMUSystem {
public:
    IMUSystem() = default;

    virtual bool initialize() = 0;

    virtual bool destroy() = 0;

    virtual bool update() = 0;

    virtual uint16_t get(int data) = 0;
};

#endif //CAHRR_IMUSYSTEM_H
