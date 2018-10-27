//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_TASK_H
#define CAHRR_TASK_H


class Task {
public:
    Task() = default;

    virtual bool initialize() = 0;

    virtual bool destroy() = 0;

    virtual bool isEnd() { return false; }

    virtual bool update() = 0;
};


#endif //CAHRR_TASK_H
