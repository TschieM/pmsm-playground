#include <yaml-cpp/yaml.h>
#include "pmsm_sim.h"

PmsmSimModel::PmsmSimModel(const string& sys_config, const string& pmsm_config) {
    YAML::Node sysConfig = YAML::LoadFile(sys_config);
    ts =  std::stod(sysConfig["sample_time"].as<std::string>());

    YAML::Node pmsmConfig = YAML::LoadFile(pmsm_config); 
    phaseR = std::stod(pmsmConfig["phase_resistance"].as<std::string>());
    phaseL = std::stod(pmsmConfig["phase_inductance"].as<std::string>());

    phaseCurrent.fill({0.0, 0.0, 0.0});
    phaseVoltage.fill({0.0, 0.0, 0.0});
    oldPhaseVoltage.fill({0.0, 0.0, 0.0});
}

PmsmSimModel::~PmsmSimModel() {}

void PmsmSimModel::setVoltage(const double Vdc, const struct PmsmPhaseSwitch& phaseSwitch) {
    for(auto i=PmsmPhaseId::PHASEA; i<PmsmPhaseId::NUM_PHASES; i++) {
        if(phaseSwitch.highEnd.at(i)&phaseSwitch.lowEnd.at(i)) {
           // report an short circuit error 
        }
    }
    double ppVoltage = (1 - std::accumulate(phaseSwitch.highEnd.begin(), phaseSwitch.highEnd.end(), 0)/3) * Vdc;
    double npVoltage = (1 - std::accumulate(phaseSwitch.lowEnd.begin(), phaseSwitch.lowEnd.end(), 0)/3) * Vdc;
    for(auto i=PmsmPhaseId::PHASEA; i<PmsmPhaseId::NUM_PHASES; i++) {
        phaseVoltage.at(i) = ppVoltage*phaseSwitch.highEnd.at(i) - npVoltage*phaseSwitch.lowEnd.at(i);
    }
}

double PmsmSimModel::getPhaseCurrent(const enum PmsmPhaseId& phaseId) {
    return phaseCurrent.at(phaseId);
}

void PmsmSimModel::updateElectricalModel() {
    for(auto i=PmsmPhaseId::PHASEA; i<PmsmPhaseId::NUM_PHASES; i++) {
        phaseCurrent.at(i) = (ts*(phaseVoltage.at(i)+oldPhaseVoltage.at(i)) + (2*phaseL - ts*phaseR)*phaseCurrent.at(i)) / (2*phaseL + ts*phaseR);
        oldPhaseVoltage.at(i) = phaseVoltage.at(i);
    }
}