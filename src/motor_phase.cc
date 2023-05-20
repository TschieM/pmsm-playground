#include "motor_phase.h"

MotorPhase::MotorPhase(const double resistor, const double inductance): R(resistor), L(inductance) {
    voltage = 0.0;
    oldVoltage = 0.0;
    current = 0.0;
}

MotorPhase::~MotorPhase() {}

void MotorPhase::setVoltage(const double val) {
    voltage = val;
}

double MotorPhase::getCurrent(){
    return current;
}

void MotorPhase::run(const double ts){
    current = (ts*(voltage+oldVoltage) + (2*L - ts*R)*current) / (2*L + ts*R);
    oldVoltage = voltage;
}