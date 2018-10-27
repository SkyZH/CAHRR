//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_DEBUGSYSTEM_H
#define CAHRR_DEBUGSYSTEM_H

#include <string>

class DebugSystem {
public:
    DebugSystem() = default;

    virtual bool initialize() = 0;
    virtual bool error(const char* &src, const char* &message) = 0;
    virtual bool info(const char* &src, const char* &message) = 0;
    virtual bool error(const std::string &src, const std::string &message) = 0;
    virtual bool info(const std::string &src, const std::string &message) = 0;
    virtual bool destroy() = 0;
};

#endif //CAHRR_DEBUGSYSTEM_H
