//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CHARR_CHASSISSYSTEM_H
#define CHARR_CHASSISSYSTEM_H

extern int chassis_sent_data_bf, chassis_sent_data_lr;

class ChassisSystem {
private:
    bool initialized;
public:
    ChassisSystem();
    bool initialize();
    bool update();
    bool destroy();
    bool data();

    int BackForward, LeftRight;
};

#endif //CHARR_CHASSISSYSTEM_H
