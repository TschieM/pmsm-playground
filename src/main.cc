#include "pmsm.h"

int main() {
    Pmsm motor("../configs/pmsm.yaml");
    motor.run(0.1);
    return 0;
}