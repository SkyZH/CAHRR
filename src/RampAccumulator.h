//
// Created by Alex Chi on 2018/10/29.
//

#ifndef CAHRR_RAMPACCUMULATOR_H
#define CAHRR_RAMPACCUMULATOR_H


template<typename T>
class RampAccumulator {
public:
    T lst_data, ramp_limit;

    bool do_reset;

    RampAccumulator(T ramp_limit) : ramp_limit(ramp_limit), do_reset(true), lst_data(0) {
    }

    void reset() {
        this->do_reset = true;
    }

    void data(T data) {
        this->do_reset = false;
        this->lst_data = data;
    }

    T calc(T target) {
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
};

#endif //CAHRR_RAMPACCUMULATOR_H
