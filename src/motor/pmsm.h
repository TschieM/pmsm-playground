#ifndef _PMSM_H_
#define _PMSM_H_

#include <array>
#include <string>
#include <memory>
#include <Eigen/Dense>

class PMSM_Motor {
 public:
  PMSM_Motor(const std::string &pmsm_config, const double ts);
  ~PMSM_Motor();
  void setVoltage(const uint8_t id, const double val);
  void setLoad(const double val);
  double getPosition();
  double getCurrent(const uint8_t id);
  void update();

 private:
  void updateFlux();
  void updateVoltage();
  void updateCurrentPhaseModel();
  void updateCurrentDQModel();
  void updateDynamic();
  void clarke_park_tf(Eigen::Vector3d &in, Eigen::Vector2d &out);
  void inv_clarke_park_tf(Eigen::Vector2d &in, Eigen::Vector3d &out);

  struct {
    double Rs;
    double Ls;
    double Lm;
    double Lms;
    double Ld;
    double Lq;
    double phi_m;
    double pp;
    double inertia;
  } params;

  Eigen::Vector3d lineVoltage;
  Eigen::Vector3d phaseVoltage;
  Eigen::Vector3d oldPhaseVoltage;
  Eigen::Vector3d phaseCurrent;
  Eigen::Vector3d phaseFlux;
  Eigen::Vector3d oldPhaseFlux;
  Eigen::Vector2d dqCurrent;
  Eigen::Vector2d dqVoltage;
  Eigen::Vector2d oldDqVoltage;

  Eigen::Matrix2d dqA;
  Eigen::Matrix2d dqB;
  Eigen::Matrix2d dqW;

  Eigen::Matrix3d phaseA;
  Eigen::Matrix3d phaseB;
  Eigen::Matrix3d phaseW;

  double pos_e;
  double pos_m;
  double velocity;
  double torque;
  double load;
  double ts;
};

#endif