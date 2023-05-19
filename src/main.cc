#include "pmsm_sim.h"

int main() {
    PmsmSimModel pmsm("../configs/sim_sys.yaml", "../configs/pmsm.yaml");
    pmsm.updateModel();
    return 0;
}