//
// Created by Alex Chi on 2018/10/27.
//

#ifndef CAHRR_ROTATEACCUMULATOR_H
#define CAHRR_ROTATEACCUMULATOR_H


class RotateAccumulator {
public:
    int round, overflow, lst_data, max_data, offset_data;
    bool do_calibrate;

    RotateAccumulator(int max_data);

    void reset();

    void data(int data);

    int get_round();

    int get_overflow();

    void calibrate();
};


#endif //CAHRR_ROTATEACCUMULATOR_H
