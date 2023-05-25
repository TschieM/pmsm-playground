#include <yaml-cpp/yaml.h>
#include <numeric>
#include <cmath>
#include <algorithm>
#include "pmsm.h"

PMSM_Motor::PMSM_Motor(const std::string& pmsm_config, const double ts): ts(ts) {
    YAML::Node config = YAML::LoadFile(pmsm_config); 
    params.Rs = std::stod(config["phase_resistance"].as<std::string>());
    params.Ls = std::stod(config["phase_inductance"].as<std::string>());
    params.Lms = std::stod(config["mutal_inductance"].as<std::string>());;
    params.Lm = std::stod(config["inductance_fluctuation"].as<std::string>());
    params.pp = std::stod(config["pole_pairs"].as<std::string>());
    params.inertia = std::stod(config["inertia"].as<std::string>());
    double kt = std::stod(config["motor_constant"].as<std::string>());


    params.phi_m = kt / (params.pp * 3/2);
    lineVoltage.fill(0);
    phaseVoltage.fill(0);
    phaseCurrent.fill(0);
    phaseFlux.fill(0);
    oldPhaseFlux.fill(0);
}

PMSM_Motor::~PMSM_Motor() {}

void PMSM_Motor::setVoltage(const uint8_t id, const double val) {
    lineVoltage.at(id) = val;
}

void PMSM_Motor::setLoad(const double val) {
    load = val;
}

double PMSM_Motor::getPosition() {
    return pos_m;
}

double PMSM_Motor::getCurrent(const uint8_t id) {
    return phaseCurrent.at(id);
}

void PMSM_Motor::update() {
    updateFlux();
    updateCurrent();
    updateDynamic();
}

void PMSM_Motor::updateFlux(){
    double Laa = params.Ls+params.Lm*cos(2*pos_e);
    double Lbb = params.Ls+params.Lm*cos(2*(pos_e-M_PI*2/3));
    double Lcc = params.Ls+params.Lm*cos(2*(pos_e+M_PI*2/3));
    double Lab = - (params.Lms+params.Lm*cos(2*(pos_e+M_PI/6)));
    double Lac = - (params.Lms+params.Lm*cos(2*(pos_e+M_PI/6+M_PI*2/3)));
    double Lbc = - (params.Lms+params.Lm*cos(2*(pos_e+M_PI/6-M_PI*2/3)));
    double Phi_am = params.phi_m * cos(pos_e);
    double Phi_bm = params.phi_m * cos(pos_e - M_PI*2/3);
    double Phi_cm = params.phi_m * cos(pos_e + M_PI*2/3);
    phaseFlux.at(0) = Laa*phaseCurrent.at(0) + Lab*phaseCurrent.at(1) + Lac*phaseCurrent.at(2) + Phi_am;
    phaseFlux.at(1) = Lab*phaseCurrent.at(0) + Lbb*phaseCurrent.at(1) + Lbc*phaseCurrent.at(2) + Phi_bm;
    phaseFlux.at(2) = Lac*phaseCurrent.at(0) + Lbc*phaseCurrent.at(1) + Lcc*phaseCurrent.at(2) + Phi_cm;
}

void PMSM_Motor::updateCurrent(){
    double Vdc = std::max_element(lineVoltage.begin(), lineVoltage.end());
    double postivePhaseVoltage = Vdc - std::accumulate(lineVoltage.begin(), lineVoltage.end(), 0) / 3;
    double negativePhaseVoltage = Vdc - postivePhaseVoltage;
    for(uint8_t i = 0; i < 3; i++) {
        phaseVoltage.at(i) = lineVoltage.at(i) > 0 ? postivePhaseVoltage : negativePhaseVoltage;
    } 

    for (uint8_t i = 0; i < 3; i++) {
        phaseCurrent.at(i) = (phaseVoltage.at(i) - (phaseFlux.at(i)-oldPhaseFlux.at(i))/ts) / params.Rs;
        oldPhaseFlux.at(i) = phaseFlux.at(i);
    }
}

void PMSM_Motor::updateDynamic(){
    double Ld = params.Ls + params.Lms + 3.0/2.0*params.Lm;
    double Lq = params.Ls + params.Lms - 3.0/2.0*params.Lm;
    double id = (sin(pos_e)*phaseCurrent.at(0) + sin(pos_e-M_PI*2/3)*phaseCurrent.at(1) + sin(pos_e+M_PI*2/3)*phaseCurrent.at(2)) * 2/3;
    double iq = (cos(pos_e)*phaseCurrent.at(0) + cos(pos_e-M_PI*2/3)*phaseCurrent.at(1) + cos(pos_e+M_PI*2/3)*phaseCurrent.at(2)) * 2/3;
    torque = params.pp * (iq*params.phi_m + (Ld-Lq)*id*iq) * 3/2;
    velocity += (torque-load)/params.inertia*ts;
    pos_m += velocity*ts;
    pos_m = std::fmod(pos_m, M_PI*2);
    pos_e += params.pp*pos_m;
    pos_e = std::fmod(pos_e, M_PI*2);
}