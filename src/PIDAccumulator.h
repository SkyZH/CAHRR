//
// Created by Alex Chi on 2018/10/29.
//

#ifndef CAHRR_PIDACCUMULATOR_H
#define CAHRR_PIDACCUMULATOR_H


class PIDAccumulator {
protected:
    double Kp, Ki, Kd;
    double output_min, output_max;
    double prev_error, total_error;
public:
    PIDAccumulator();

    bool set_pid(double Kp, double Ki, double Kd);

    bool set_output(double output_min, double output_max);

    virtual double calc(double error) = 0;

    bool reset();
};

class PIDRateAccumulator : public PIDAccumulator {
public:
    PIDRateAccumulator() = default;

    virtual double calc(double error);
};

class PIDDisplacementAccumulator : public PIDAccumulator {
public:
    PIDDisplacementAccumulator() = default;

    virtual double calc(double error);
};


#endif //CAHRR_PIDACCUMULATOR_H
