//
// Created by Alex Chi on 2018/10/26.
//

#include "AvgAccumulator.h"

AvgAccumulator::AvgAccumulator() {
    this->reset();
}

void AvgAccumulator::reset() {
    this->sum_data = 0;
    this->n = 0;
}

void AvgAccumulator::data(int data) {
    this->sum_data += data;
    this->n++;
}

int AvgAccumulator::sum() {
    int result = this->sum_data / this->n;
    this->reset();
    return result;
}
