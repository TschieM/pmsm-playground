#include "inverter.h"
#include <numeric>

Inverter::Inverter(const Pmsm& connected_pmsm, const double Vdc): pmsm(connected_pmsm), Vdc(Vdc) {
    highMos.fill(0);
    lowMos.fill(0);
}

Inverter::~Inverter(){}

void Inverter::closeHighEndMosfet(const uint8_t phase){
    highMos.at(phase) = true;
}

void Inverter::openHighEndMosfet(const uint8_t phase){
    highMos.at(phase) = false;
}

void Inverter::closeLowEndMosfet(const uint8_t phase){
    lowMos.at(phase) = true;
}

void Inverter::openLowEndMosfet(const uint8_t phase){
    lowMos.at(phase) = false;
}

void Inverter::run(){
    for(uint8_t i=0; i<3; i++) {
        if(highMos.at(i) & lowMos.at(i)) {
           // report an short circuit error 
        }
    }
    double ppVoltage = (1 - static_cast<double>(std::accumulate(highMos.begin(), highMos.end(), 0))/3) * Vdc;
    double npVoltage = (1 - static_cast<double>(std::accumulate(lowMos.begin(), lowMos.end(), 0))/3) * Vdc;
    for(uint8_t i=0; i<3; i++) {
        pmsm.setPhaseVoltage(i, ppVoltage*highMos.at(i) - npVoltage*lowMos.at(i));
    }
}