//
// Created by Alex Chi on 2018/10/29.
//

#include "RampAccumulator.h"

RampAccumulator::RampAccumulator(long long ramp_limit) : ramp_limit(ramp_limit), do_reset(true), lst_data(0) {
}

void RampAccumulator::reset() {
    this->do_reset = true;
}

void RampAccumulator::data(long long data) {
    this->do_reset = false;
    this->lst_data = data;
}

long long RampAccumulator::calc(long long target) {
    if (this->do_reset)
        return target;
    else {
        if (target < lst_data - ramp_limit) {
            return lst_data - ramp_limit;
        } else if (target > lst_data + ramp_limit) {
            return lst_data + ramp_limit;
        } else {
            return target;
        }
    }
}
