//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_AVGACCUMULATOR_H
#define CAHRR_AVGACCUMULATOR_H


class AvgAccumulator {
public:
    int sum_data, n;

    AvgAccumulator();

    void reset();

    void data(int data);

    int sum();
};


#endif //CAHRR_AVGACCUMULATOR_H
