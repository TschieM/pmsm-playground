#ifndef _PMSM_SIM_H_
#define _PMSM_SIM_H_

#include <array>
#include <string>

struct PmsmPhaseSwitch {
  std::array<bool, 3> highEnd = {false, false, false};
  std::array<bool, 3> lowEnd = {false, false, false};
};

class PmsmSimModel {
 public:
  PmsmSimModel(const std::string &sys_config, const std::string &pmsm_config);
  ~PmsmSimModel();
  void setVoltage(const double Vdc, const struct PmsmPhaseSwitch &phaseSwitch);
  double getPhaseCurrent(const uint8_t &phaseId);
  void updateModel();

 private:
  void updateElectricalModel();

  std::array<double, 3> phaseCurrent;
  std::array<double, 3> phaseVoltage;
  std::array<double, 3> oldPhaseVoltage;
  // pmsm parameters
  double phaseR;
  double phaseL;
  // simulation parameters
  uint32_t ts;
};

#endif