//
// Created by Alex Chi on 2018/10/27.
//

#include "MockDebugSystem.h"

std::string logged_data = "";

bool MockDebugSystem::initialize() {
    this->info("DebugSystem", "system initialized");
    return true;
}

bool MockDebugSystem::error(const char *&src, const char *&message) {
    return this->_error(src, message);
}

bool MockDebugSystem::info(const char *&src, const char *&message) {
    return this->_info(src, message);
}

bool MockDebugSystem::error(const std::string &src, const std::string &message) {
    return this->_error(src, message);
}

bool MockDebugSystem::info(const std::string &src, const std::string &message) {
    return this->_info(src, message);
}

bool MockDebugSystem::destroy() {
    this->info("DebugSystem", "system halted");
    return true;
}

bool MockDebugSystem::_error(const std::string &src, const std::string &message) {
    logged_data = "[" + src + "][E] " + "0" + " " + message;
    return true;
}

bool MockDebugSystem::_info(const std::string &src, const std::string &message) {
    logged_data = "[" + src + "][I] " + "0" + " " + message;
    return true;
}

bool MockDebugSystem::set_led(int id, bool val) {
    return true;
}

bool MockDebugSystem::toggle_led(int id) {
    return true;
}

bool MockDebugSystem::alive() {
    return true;
}
