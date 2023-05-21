#ifndef _PMSM_H_
#define _PMSM_H_

#include "motor_phase.h"
#include <array>
#include <string>
#include <memory>

class Pmsm {
 public:
  Pmsm(const std::string &pmsm_config);
  ~Pmsm();
  void setPhaseVoltage(const uint8_t phaseId, const double val);
  double getPhaseCurrent(const uint8_t phaseId);
  void run(const double ts);

 private:
  void updateElectric(const double ts);

  std::array<std::shared_ptr<MotorPhase>, 3> phases;
};

#endif