#ifndef FUZZY_HPP
#define FUZZY_HPP

#include <cmath>

class Fuzzy{
private:
    double range[2], SP, tot_range;
    bool inverse;

public:
    Fuzzy(double bounds[2], double setpoint=0, bool invert=false){
        range[0] = bounds[0];
        range[1] = bounds[1];

        SP = setpoint;
        inverse = invert;

        tot_range = std::abs(range[1]-range[0]);
    }

    void set_setpoint(double setpoint){
        SP = setpoint;
    }

    void set_bounds(double bounds[2]){
        range[0] = bounds[0];
        range[1] = bounds[1];
        tot_range = std::abs(range[1]-range[0]);
    }

    double get_correction(double value){
        value = std::abs(value/tot_range);
        if (inverse){return 1 - value;}
        else{return value;}
    }
};

#endif