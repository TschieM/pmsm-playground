#ifndef _ADC_H_
#define _ADC_H_

#include <cstdint>
#include <vector>

class ADC {
    public:
        ADC(const double u_ref, const uint32_t ch_num, const uint32_t res_in_bits);
        void setAnalogValue(const uint32_t channel, const double val);
        uint32_t getValue(const uint32_t channel);
        void update();
    private:
        double uadc;
        uint32_t res;
        std::vector<double> aVals;
        std::vector<double> dVals;
};

#endif