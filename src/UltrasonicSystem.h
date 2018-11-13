//
// Created by Alex Chi on 2018/11/13.
//

#ifndef CAHRR_ULTRASONICSYSTEM_H
#define CAHRR_ULTRASONICSYSTEM_H


class UltrasonicSystem {
public:
    UltrasonicSystem() = default;

    virtual bool trigger() = 0;

    virtual bool initialize() = 0;

    virtual bool update() = 0;

    virtual bool destroy() = 0;

    virtual double distance() = 0;

    virtual uint16_t time() = 0;
};


#endif //CAHRR_ULTRASONICSYSTEM_H
