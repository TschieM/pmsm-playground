#include <yaml-cpp/yaml.h>
#include <numeric>
#include "pmsm_sim.h"

PmsmSimModel::PmsmSimModel(const std::string& sys_config, const std::string& pmsm_config) {
    YAML::Node sysConfig = YAML::LoadFile(sys_config);
    ts =  std::stod(sysConfig["sample_time"].as<std::string>());

    YAML::Node pmsmConfig = YAML::LoadFile(pmsm_config); 
    phaseR = std::stod(pmsmConfig["phase_resistance"].as<std::string>());
    phaseL = std::stod(pmsmConfig["phase_inductance"].as<std::string>());

    for(uint8_t i=0; i<3; i++) {
      phaseCurrent.at(i) = 0.0;
      phaseVoltage.at(i) = 0.0;
      oldPhaseVoltage.at(i) = 0.0;
    }
}

PmsmSimModel::~PmsmSimModel() {}

void PmsmSimModel::setVoltage(const double Vdc, const struct PmsmPhaseSwitch& invertor) {
    for(uint8_t i=0; i<3; i++) {
        if(invertor.highEnd.at(i)&invertor.lowEnd.at(i)) {
           // report an short circuit error 
        }
    }
    double ppVoltage = (1 - static_cast<double>(std::accumulate(invertor.highEnd.begin(), invertor.highEnd.end(), 0))/3) * Vdc;
    double npVoltage = (1 - static_cast<double>(std::accumulate(invertor.lowEnd.begin(), invertor.lowEnd.end(), 0))/3) * Vdc;
    for(uint8_t i=0; i<3; i++) {
        phaseVoltage.at(i) = ppVoltage*invertor.highEnd.at(i) - npVoltage*invertor.lowEnd.at(i);
    }
}

double PmsmSimModel::getPhaseCurrent(const uint8_t& phaseId) {
    return phaseCurrent.at(phaseId);
}

void PmsmSimModel::updateModel() {
    updateElectricalModel();
}

void PmsmSimModel::updateElectricalModel() {
    for(uint8_t i=0; i<3; i++) {
        phaseCurrent.at(i) = (ts*(phaseVoltage.at(i)+oldPhaseVoltage.at(i)) + (2*phaseL - ts*phaseR)*phaseCurrent.at(i)) / (2*phaseL + ts*phaseR);
        oldPhaseVoltage.at(i) = phaseVoltage.at(i);
    }
}