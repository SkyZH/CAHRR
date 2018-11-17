//
// Created by Alex Chi on 2018/11/17.
//

#ifndef CAHRR_UTILS_H
#define CAHRR_UTILS_H

#include <cmath>

template<typename T>
inline T clamp(T in, T min, T max) {
    return (in < min ? min : (in > max ? max : in));
}

template<typename T>
inline T cycle_err(T err, T range) {
    if (abs(err) > range / 2) {
        if (err > 0) {
            return err - range;
        } else {
            return err + range;
        }
    }
    return err;
}


template<typename T>
inline T cycle_err(T target, T current, T min, T max) {
    T range = max - min;
    T err = (target - current) % range;
    return cycle_err(err, range);
}

inline double cycle_err_double(double err, double range) {
    if (fabs(err) > range / 2) {
        if (err > 0) {
            return err - range;
        } else {
            return err + range;
        }
    }
    return err;
}

inline double cycle_err_double(double target, double current, double min, double max) {
    double range = max - min;
    double err = fmod((target - current), range);
    return cycle_err_double(err, range);
}

#endif //CAHRR_UTILS_H
