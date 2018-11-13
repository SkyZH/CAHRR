//
// Created by Alex Chi on 2018/10/26.
//

#ifndef CAHRR_AVGACCUMULATOR_H
#define CAHRR_AVGACCUMULATOR_H

template <typename T>
class AvgAccumulator {
public:
    T sum_data;
    int n;

    AvgAccumulator();

    void reset();

    void data(T data);

    T sum();
};

template <typename T>
AvgAccumulator<T>::AvgAccumulator() : sum_data(0), n(0) {
    this->reset();
}

template <typename T>
void AvgAccumulator<T>::reset() {
    this->sum_data = 0;
    this->n = 0;
}

template <typename T>
void AvgAccumulator<T>::data(T data) {
    this->sum_data += data;
    this->n++;
}

template <typename T>
T AvgAccumulator<T>::sum() {
    if (this->n == 0) return 0;
    T result = this->sum_data / this->n;
    this->reset();
    return result;
}


#endif //CAHRR_AVGACCUMULATOR_H
