#ifndef _PMSM_H_
#define _PMSM_H_

#include <array>
#include <string>
#include <memory>

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
  void updateCurrent();
  void updateDynamic();

  std::array<double, 3> lineVoltage;
  std::array<double, 3> phaseVoltage;
  std::array<double, 3> phaseCurrent;
  std::array<double, 3> phaseFlux;
  std::array<double, 3> oldPhaseFlux;
  struct {
    double Rs;
    double Ls;
    double Lm;
    double Lms;
    double phi_m;
    double pp;
    double inertia;
  } params;
  double pos_e;
  double pos_m;
  double velocity;
  double torque;
  double load;
  double ts;
};

#endif