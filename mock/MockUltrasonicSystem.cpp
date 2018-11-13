//
// Created by Alex Chi on 2018/11/13.
//


#include "MockUltrasonicSystem.h"

bool ultrasonic_data_sent = false;
int now_time = 0;

MockUltrasonicSystem::MockUltrasonicSystem() : UltrasonicSystem(), delta_time(0), lst_sent(0), data_available(false), available_time(0) {

}

bool MockUltrasonicSystem::trigger() {
    this->delta_time = now_time - lst_sent;
    lst_sent = now_time;
    this->data_available = true;
    this->send_data();
    return true;
}

bool MockUltrasonicSystem::initialize() {
    this->send_data();
    return true;
}

bool MockUltrasonicSystem::update() {
    if (this->data_available) {
        this->data_available = false;
        this->available_time = this->delta_time;
    } else {
        this->available_time = 0;
    }
    return true;
}

bool MockUltrasonicSystem::destroy() {
    return true;
}

double MockUltrasonicSystem::distance() {
    return 0;
}

uint16_t MockUltrasonicSystem::time() {
    return this->available_time;
}

void MockUltrasonicSystem::send_data() {
    this->lst_sent = now_time;
    ultrasonic_data_sent = true;
}
