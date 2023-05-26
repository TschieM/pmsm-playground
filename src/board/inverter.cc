#include "inverter.h"
#include <numeric>
#include <cstdint>

Inverter::Inverter(const double Vdc): Vdc(Vdc) {
    mosfets.fill(false);
    lineVotages.fill(0);
}

Inverter::~Inverter(){}

void Inverter::setMosfetStatus(const int id, const bool status) {
    mosfets.at(id) = status;
}

double Inverter::getLineVoltage(const int id) {
    return lineVotages.at(id);
}

void Inverter::update(){
    for(uint8_t i=0; i<3; i++) {
        if(mosfets.at(i) && mosfets.at(i+3)) {
            // report short error
        }
    }

    for(uint8_t i=0; i<3; i++) {
        lineVotages.at(i) = Vdc*mosfets.at(i);
    }
}