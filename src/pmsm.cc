#include <yaml-cpp/yaml.h>
#include <numeric>
#include "motor_phase.h"
#include "pmsm.h"

Pmsm::Pmsm(const std::string& pmsm_config) {
    YAML::Node pmsmConfig = YAML::LoadFile(pmsm_config); 
    double R = std::stod(pmsmConfig["phase_resistance"].as<std::string>());
    double L = std::stod(pmsmConfig["phase_inductance"].as<std::string>());

    for(uint8_t i=0; i<3; i++) {
        phases.at(i) = std::make_shared<MotorPhase>(R, L);
    }
}

Pmsm::~Pmsm() {}

void Pmsm::setPhaseVoltage(const uint8_t phaseId, const double val) {
    phases.at(phaseId)->setVoltage(val);
}

double Pmsm::getPhaseCurrent(const uint8_t phaseId) {
    return phases.at(phaseId)->getCurrent();
}

void Pmsm::run(const double ts) {
    updateElectric(ts);
}

void Pmsm::updateElectric(const double ts) {
    for(uint8_t i=0; i<3; i++) {
        phases.at(i)->run(ts);
    }
}