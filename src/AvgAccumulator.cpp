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

void AvgAccumulator::data(long long data) {
    this->sum_data += data;
    this->n++;
}

long long AvgAccumulator::sum() {
    long long result = this->sum_data / this->n;
    this->reset();
    return result;
}
