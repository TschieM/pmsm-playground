#include "current_meas.h"

CurrentMeas::CurrentMeas(const double rm, const double Kopamp, const double offset){
    r = rm;
    K = Kopamp;
    off = offset;

    current = 0.0;
    measVal = 0.0;
}

void CurrentMeas::setCurrent(const double val){
    current = val;
}

double CurrentMeas::getMeasurement(){
    return measVal;
}

void CurrentMeas::update(){
    measVal = current * r * K + off;
}