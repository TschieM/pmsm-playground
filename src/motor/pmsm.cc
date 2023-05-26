#include <yaml-cpp/yaml.h>
#include <numeric>
#include <cmath>
#include <algorithm>
#include "pmsm.h"

PMSM_Motor::PMSM_Motor(const std::string& pmsm_config, const double ts): ts(ts) {
    YAML::Node config = YAML::LoadFile(pmsm_config); 
    params.Rs = std::stod(config["phase_resistance"].as<std::string>());
    params.Ls = std::stod(config["phase_inductance"].as<std::string>());
    params.Ld = std::stod(config["phase_d_inductance"].as<std::string>());;
    params.Lq = std::stod(config["phase_q_inductance"].as<std::string>());
    params.pp = std::stod(config["pole_pairs"].as<std::string>());
    params.inertia = std::stod(config["inertia"].as<std::string>());
    double kt = std::stod(config["motor_constant"].as<std::string>());


    params.phi_m = kt / (params.pp * 3/2);
    params.Lms = (params.Ld+params.Lq-2*params.Ls)/2;
    params.Lm = (params.Ld-params.Lq)/3;

    lineVoltage = Eigen::Vector3d::Zero();
    phaseVoltage = Eigen::Vector3d::Zero();
    oldPhaseVoltage = Eigen::Vector3d::Zero();
    phaseCurrent = Eigen::Vector3d::Zero();
    phaseFlux = Eigen::Vector3d::Zero();
    oldPhaseFlux = Eigen::Vector3d::Zero();
    dqCurrent = Eigen::Vector2d::Zero();
    dqVoltage = Eigen::Vector2d::Zero();
    oldDqVoltage = Eigen::Vector2d::Zero();

    pos_e = 0;
    pos_m = 0;
    velocity = 0;
    torque = 0;
    load = 0;
}

PMSM_Motor::~PMSM_Motor() {}

void PMSM_Motor::setVoltage(const uint8_t id, const double val) {
    // lineVoltage.at(id) = val;
    lineVoltage(id) = val;
}

void PMSM_Motor::setLoad(const double val) {
    load = val;
}

double PMSM_Motor::getPosition() {
    return pos_m;
}

double PMSM_Motor::getCurrent(const uint8_t id) {
    // return phaseCurrent.at(id);
    return phaseCurrent(id);
}

void PMSM_Motor::update() {
    updateCurrentPhaseModel();
    updateDynamic();
}

void PMSM_Motor::updateFlux(){
    Eigen::Matrix3d L {
         {params.Ls+params.Lm*cos(2*pos_e), -(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6))), -(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6+M_PI*2/3)))},
         {-(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6))), params.Ls+params.Lm*cos(2*(pos_e-M_PI*2/3)), -(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6-M_PI*2/3)))},
         {-(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6+M_PI*2/3))), -(params.Lms+params.Lm*cos(2*(pos_e+M_PI/6-M_PI*2/3))), params.Ls+params.Lm*cos(2*(pos_e+M_PI*2/3))}
    };
    Eigen::Vector3d Phi {params.phi_m * cos(pos_e), params.phi_m * cos(pos_e - M_PI*2/3), params.phi_m * cos(pos_e + M_PI*2/3)};
    phaseFlux = L * phaseCurrent + Phi;
}

void PMSM_Motor::updateVoltage() {
    double Vdc = lineVoltage.maxCoeff();
    double postivePhaseVoltage = Vdc - lineVoltage.sum()/3;
    double negativePhaseVoltage = Vdc - postivePhaseVoltage;
    for(uint8_t i = 0; i < 3; i++) {
        phaseVoltage(i) = lineVoltage(i) > 0 ? postivePhaseVoltage : negativePhaseVoltage;
    } 
    clarke_park_tf(phaseVoltage, dqVoltage);
}

void PMSM_Motor::updateCurrentPhaseModel(){
    updateFlux();
    updateVoltage();
    clarke_park_tf(phaseCurrent, dqCurrent);
}

void PMSM_Motor::updateCurrentDQModel(){
    updateVoltage();
    
    Eigen::Matrix2d cA {
        {-params.Rs/params.Ld, params.Lq/params.Ld*params.pp*velocity}, 
        {-params.Ld/params.Lq*params.pp*velocity, -params.Rs/params.Lq}
    };
    Eigen::Matrix2d cB {{1/params.Ld, 0}, {0, 1/params.Lq}};
    Eigen::Vector2d cW {0, 1};

    Eigen::Matrix2d dA = (Eigen::Matrix2d::Identity()-ts/2*cA).inverse() * (Eigen::Matrix2d::Identity()+ts/2*cA);
    Eigen::Matrix2d dB = (Eigen::Matrix2d::Identity()-ts/2*cA).inverse() * cB;
    Eigen::Vector2d dW = (Eigen::Matrix2d::Identity()-ts/2*cA).inverse() * cW;

    dqCurrent = dA*dqCurrent + dB*(dqVoltage+oldDqVoltage) + dW*params.phi_m*params.pp*velocity/params.Lq;
    oldDqVoltage = dqVoltage;

    inv_clarke_park_tf(dqCurrent, phaseCurrent);
}

void PMSM_Motor::updateDynamic(){
    torque = params.pp * (dqCurrent(1)*params.phi_m + (params.Ld-params.Lq)*dqCurrent(0)*dqCurrent(1)) * 3/2;
    velocity += (torque-load)/params.inertia*ts;
    pos_m += velocity*ts;
    pos_m = std::fmod(pos_m, M_PI*2);
    pos_e += params.pp*pos_m;
    pos_e = std::fmod(pos_e, M_PI*2);
}

void PMSM_Motor::clarke_park_tf(Eigen::Vector3d &in, Eigen::Vector2d &out) {
    Eigen::Matrix<double, 2, 3> tf {
        {sin(pos_e), sin(pos_e-M_PI*2/3), sin(pos_e+M_PI*2/3)}, 
        {cos(pos_e), cos(pos_e-M_PI*2/3), cos(pos_e+M_PI*2/3)}
    };
    out  = tf * in;
}

void PMSM_Motor::inv_clarke_park_tf(Eigen::Vector2d &in, Eigen::Vector3d &out) {
    Eigen::Matrix<double, 3, 2> tf {
        {cos(pos_e), -sin(pos_e)},
        {cos(pos_e-M_PI*2/3), -sin(pos_e-M_PI*2/3)},
        {cos(pos_e+M_PI*2/3), -sin(pos_e+M_PI*2/3)}
    };
    out  = tf * in;
}