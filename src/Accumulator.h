//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_ACCUMULATOR_H
#define CAHRR_ACCUMULATOR_H


class Accumulator {
public:
    int sum_data, n;

    Accumulator();

    void reset();

    void data(int data);

    int sum();
};


#endif //CAHRR_ACCUMULATOR_H
