#ifndef ON_OFF_HPP
#define ON_OFF_HPP

#include <cmath>

class On_Off
{
private:
    double SP = 0;
    double TOL = 10e-3;

public:
    On_Off(double setpoint=0);
    void set_setpoint(double setpoint);
    void set_tolerance(double tolerance);
    bool get_correction(double value);
};

On_Off::On_Off(double setpoint=0){
    //Optional arguments: setpoint
    On_Off::SP = setpoint;
}

void On_Off::set_setpoint(double setpoint){
    //Method sets the setpoint to the double value entered.
    On_Off::SP = setpoint;
}

void On_Off::set_tolerance(double tolerance){
    //Method sets the tolerance.
    On_Off::TOL = tolerance;
}

bool On_Off::get_correction(double value){
    if (std::abs(On_Off::SP - value) > On_Off::TOL){return true;}
    else{return false;}
}

#endif