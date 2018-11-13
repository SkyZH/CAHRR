//
// Created by Alex Chi on 2018/10/27.
//

#include "RotateAccumulator.h"

RotateAccumulator::RotateAccumulator(long long max_data) : max_data(max_data), round(0), overflow(0), lst_data(0),
                                                           offset_data(0), do_calibrate(false) {
    this->reset();
    this->calibrate();
}

void RotateAccumulator::reset() {
    this->round = this->overflow = this->lst_data = 0;
}

void RotateAccumulator::data(long long data) {
    if (this->do_calibrate) {
        this->do_calibrate = false;
        this->offset_data = data;
    }
    long long __data = ((data - offset_data) % this->max_data + this->max_data) % this->max_data;
    if (__data - this->lst_data > max_data / 2) this->round--;
    else if (__data - this->lst_data < -max_data / 2) this->round++;
    this->overflow = __data;
    this->lst_data = __data;
}

long long RotateAccumulator::get_round() {
    return this->round;
}

long long RotateAccumulator::get_overflow() {
    return this->overflow;
}

void RotateAccumulator::calibrate() {
    this->do_calibrate = true;
    this->offset_data = 0;
}
