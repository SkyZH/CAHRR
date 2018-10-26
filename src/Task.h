//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_TASK_H
#define CAHRR_TASK_H


class Task {
public:
    Task() = default;
    virtual bool initialize() { return false; };
    virtual bool destroy() { return false; };
    virtual bool isEnd() { return false; };
    virtual bool update() { return false; };
};


#endif //CAHRR_TASK_H
