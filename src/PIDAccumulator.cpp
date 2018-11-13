//
// Created by Alex Chi on 2018/10/29.
//

#include "PIDAccumulator.h"

inline double PID_clamp(double result, double min_result, double max_result) {
    return result < min_result ? min_result : (result > max_result ? max_result : result);
}
bool PIDAccumulator::set_pid(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    return true;
}

bool PIDAccumulator::set_output(double output_min, double output_max) {
    this->output_max = output_max;
    this->output_min = output_min;
    return true;
}

bool PIDAccumulator::reset() {
    prev_error = total_error = 0;
    return true;
}

PIDAccumulator::PIDAccumulator() : Kp(0), Ki(0), Kd(0), output_min(0), output_max(0), prev_error(0), total_error(0) {

}

double PIDRateAccumulator::calc(double error) {
    if (Kp != 0) {
        total_error = PID_clamp(total_error + error,
                output_min / Kp,
                output_max / Kp);
    }
    double result = Kd * error + Kp * total_error;
    return result;
}

double PIDDisplacementAccumulator::calc(double error) {
    if (Ki != 0) {
        total_error = PID_clamp(total_error + error,
                    output_min / Ki,
                    output_max / Ki);
    }
    double result = Kp * error + Ki * total_error + Kd * (error - prev_error);
    prev_error = error;
    return result;
}
