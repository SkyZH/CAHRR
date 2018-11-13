//
// Created by Alex Chi on 2018/11/13.
//

#ifndef CAHRR_DELTAACCUMULATOR_H
#define CAHRR_DELTAACCUMULATOR_H

template <typename T>
class DeltaAccumulator {
public:
    bool do_reset;
    T lst_data;
    DeltaAccumulator() : do_reset(true), lst_data(0) {
    }
    void reset() {
        this->do_reset = true;
    }
    T delta(T data) {
        if (this->do_reset) {
            this->do_reset = false;
            this->lst_data = data;
            return 0;
        } else {
            T result = data - lst_data;
            lst_data = data;
            return result;
        }
    }
};


#endif //CAHRR_DELTAACCUMULATOR_H
