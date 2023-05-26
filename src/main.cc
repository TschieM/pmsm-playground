#include "pmsm.h"

int main() {
    PMSM_Motor motor("../configs/pmsm.yaml", 0.1);
    motor.update();
    return 0;
}