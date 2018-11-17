//
// Created by Alex Chi on 2018/11/17.
//

#ifndef CAHRR_UTILS_H
#define CAHRR_UTILS_H
template <typename T>
inline T clamp(T in, T min, T max) {
    return (in < min ? min : (in > max ? max : in));
}
#endif //CAHRR_UTILS_H
