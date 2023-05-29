#include <algorithm>
#include "adc.h"

ADC::ADC(const double u_ref, const uint32_t ch_num, const uint32_t res_in_bits){
    uadc = u_ref;
    res = (1 << res_in_bits);
    aVals.reserve(ch_num);
    dVals.reserve(ch_num);
    std::fill(aVals.begin(), aVals.end(), 0);
    std::fill(dVals.begin(), dVals.end(), 0);
}

void ADC::setAnalogValue(const uint32_t channel, const double val){
    aVals.at(channel) = val;
}

uint32_t ADC::getValue(const uint32_t channel){
    return dVals.at(channel);
}

void ADC::update() {
    for(uint32_t i=0; i<aVals.size(); i++) {
        dVals.at(i) = res * aVals.at(i) / uadc;
    }
}
