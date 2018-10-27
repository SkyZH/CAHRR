//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_CHASSISSYSTEM_H
#define CAHRR_CHASSISSYSTEM_H

class ChassisSystem {
private:
public:
    ChassisSystem() = default;

    virtual bool initialize() = 0;

    virtual bool update() = 0;

    virtual bool destroy() = 0;

    virtual bool setSpeed(double bf, double lr) = 0;
};

#endif //CAHRR_CHASSISSYSTEM_H
