#ifndef _PMSM_SIM_H_
#define _PMSM_SIM_H_

enum PmsmPhaseId: uint8_t {
    PHASEA = 0,
    PHASEB,
    PHASEC,
    NUM_PHASES
};

struct PmsmPhaseSwitch {
    std::array<bool, NUM_PHASES> highEnd = {false, false, false};
    std::array<bool, NUM_PHASES> lowEnd = {false, false, false};
};

class PmsmSimModel {
    public:
        PmsmSimModel(const string& sys_config, const string& pmsm_config);
        ~PmsmSimModel();
        void setVoltage(const double Vdc, const struct PmsmPhaseSwitch& phaseSwitch);
        double getPhaseCurrent(const enum PmsmPhaseId& phaseId);

    private:
        void updateElectricalModel();

        std::array<double, NUM_PHASES> phaseCurrent;
        std::array<double, NUM_PHASES> phaseVoltage;
        std::array<double, NUM_PHASES> oldPhaseVoltage;
        // pmsm parameters
        double phaseR;
        double phaseL;
        // simulation parameters
        uint32_t ts; 
};

#endif