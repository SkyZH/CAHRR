//
// Created by Alex Chi on 2018/10/28.
//

#ifndef CAHRR_REMOTESYSTEM_H
#define CAHRR_REMOTESYSTEM_H

class RemoteSystem {
public:
    RemoteSystem() = default;

    virtual bool initialize() = 0;

    virtual bool destroy() = 0;

    virtual int16_t getAxis(int id) = 0;

    virtual int16_t getButton(int id) = 0;
};

#endif //CAHRR_REMOTESYSTEM_H
