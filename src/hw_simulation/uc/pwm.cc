#include "pwm.h"

Pwm::Pwm(){
    maxCnt = 0;
    cnt = 0;
    CCR = maxCnt+1;
    cnt_up = true;
}

Pwm::~Pwm(){}

void Pwm::setMaxCount(const uint32_t val){
    maxCnt = val;
}

void Pwm::setCompareReg(const uint32_t val){
    CCR = val;
}

void Pwm::setCallBackAtCCR0(void (*cb_fun)(void)) {
    ccr0_cb = cb_fun;
}

void Pwm::setCallBackAtCCRMax(void (*cb_fun)(void)) {
    ccrMax_cb = cb_fun;
}

void Pwm::run(void (*cb_func_high)(void), void (*cb_func_low)(void)){
    if(cnt_up) cnt_up = (cnt++ < maxCnt);
    else cnt_up = (cnt-- <= 0);

    if(cnt >= CCR) cb_func_high();
    else cb_func_low();

    if(cnt == maxCnt) ccrMax_cb();
    if(cnt == 0) ccr0_cb();
}