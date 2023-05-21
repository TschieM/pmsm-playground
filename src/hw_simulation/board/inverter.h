#ifndef _INVERTOR_H_
#define _INVERTOR_H_

#include "pmsm.h"
#include <array>

class Inverter {
    public:
        Inverter(const Pmsm& connected_pmsm, const double Vdc);
        ~Inverter();
        void closeHighEndMosfet(const uint8_t phase);
        void openHighEndMosfet(const uint8_t phase);
        void closeLowEndMosfet(const uint8_t phase);
        void openLowEndMosfet(const uint8_t phase);
        void run();
    private:
        Pmsm pmsm;
        std::array<bool, 3> highMos;
        std::array<bool, 3> lowMos;
        double Vdc;
};

#endif