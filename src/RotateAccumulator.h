//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_ROTATEACCUMULATOR_H
#define CAHRR_ROTATEACCUMULATOR_H


class RotateAccumulator {
public:
    long long round, overflow, lst_data, max_data, offset_data;

    bool do_calibrate;

    RotateAccumulator(long long max_data);

    void reset();

    void data(long long data);

    long long get_round();

    long long get_overflow();

    void calibrate();
};


#endif //CAHRR_ROTATEACCUMULATOR_H
