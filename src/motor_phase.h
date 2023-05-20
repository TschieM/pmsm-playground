#ifndef _MOTOR_PHASE_H_
#define _MOTOR_PHASE_H_

class MotorPhase {
  public:
    MotorPhase(const double resistor, const double inductance);
    ~MotorPhase();
    void setVoltage(const double val);
    double getCurrent();
    void run(const double ts);
  private:
    double current;
    double voltage;
    double oldVoltage;
    double R;
    double L;
};

#endif