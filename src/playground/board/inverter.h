#ifndef _INVERTOR_H_
#define _INVERTOR_H_

#include <array>

class Inverter {
    public:
        Inverter(const double Vdc);
        ~Inverter();
        void update();
        void setMosfetStatus(const int id, const bool status);
        double getLineVoltage(const int id);
    private:
        std::array<bool, 6> mosfets;
        std::array<double, 3> lineVotages;
        double Vdc;
};

#endif