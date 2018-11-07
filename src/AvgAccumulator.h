//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_AVGACCUMULATOR_H
#define CAHRR_AVGACCUMULATOR_H


class AvgAccumulator {
public:
    long long sum_data;
    int n;

    AvgAccumulator();

    void reset();

    void data(long long data);

    long long sum();
};


#endif //CAHRR_AVGACCUMULATOR_H
