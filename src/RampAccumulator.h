//
// Created by Alex Chi on 2018/10/29.
//

#ifndef CAHRR_RAMPACCUMULATOR_H
#define CAHRR_RAMPACCUMULATOR_H


class RampAccumulator {
public:
    long long lst_data, ramp_limit;
    
    bool do_reset;

    RampAccumulator(long long ramp_limit);

    void reset();

    void data(long long data);

    long long calc(long long target);
};


#endif //CAHRR_RAMPACCUMULATOR_H
