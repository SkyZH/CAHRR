//
// Created by Alex Chi on 2018/10/26.
//

#include "Accumulator.h"

Accumulator::Accumulator() {
    this->reset();
}

void Accumulator::reset() {
    this->sum_data = 0;
    this->n = 0;
}

void Accumulator::data(int data) {
    this->sum_data += data;
    this->n++;
}

int Accumulator::sum() {
    int result = this->sum_data / this->n;
    this->reset();
    return result;
}
