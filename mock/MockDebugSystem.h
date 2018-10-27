//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_MOCKDEBUGSYSTEM_H
#define CAHRR_MOCKDEBUGSYSTEM_H

#include <string>
#include "../src/DebugSystem.h"

extern std::string logged_data;

class MockDebugSystem : public DebugSystem {
private:
    bool _error(const std::string &src, const std::string &message);

    bool _info(const std::string &src, const std::string &message);

public:
    MockDebugSystem() = default;

    bool initialize();

    bool error(const char *&src, const char *&message);

    bool info(const char *&src, const char *&message);

    bool error(const std::string &src, const std::string &message);

    bool info(const std::string &src, const std::string &message);

    bool destroy();
};


#endif //CAHRR_MOCKDEBUGSYSTEM_H
