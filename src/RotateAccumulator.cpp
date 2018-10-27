//
// Created by Alex Chi on 2018/10/27.
//

#include "RotateAccumulator.h"

RotateAccumulator::RotateAccumulator(int max_data) : max_data(max_data) {
    this->reset();
    this->calibrate();
}

void RotateAccumulator::reset() {
    this->round = this->overflow = this->lst_data = 0;
}

void RotateAccumulator::data(int data) {
    if (this->do_calibrate) {
        this->do_calibrate = false;
        this->offset_data = data;
    }
    int __data = ((data - offset_data) % this->max_data + this->max_data) % this->max_data;
    if (__data - this->lst_data > max_data / 2) this->round--;
    else if (__data - this->lst_data < - max_data / 2) this->round++;
    this->overflow = __data;
    this->lst_data = __data;
}

int RotateAccumulator::get_round() {
    return this->round;
}

int RotateAccumulator::get_overflow() {
    return this->overflow;
}

void RotateAccumulator::calibrate() {
    this->do_calibrate = true;
    this->offset_data = 0;
}
