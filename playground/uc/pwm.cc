#include "pwm.h"

PWM::PWM(){
    maxCnt = 0;
    cnt = 0;
    CCR = maxCnt+1;
    cnt_up = true;
}

PWM::~PWM(){}

void PWM::setMaxCount(const uint32_t val){
    maxCnt = val;
}

void PWM::setCompareReg(const uint32_t val){
    CCR = val;
}

void PWM::setCallBackAtCCR0(void (*cb_fun)(void)) {
    ccr0_cb = cb_fun;
}

void PWM::setCallBackAtCCRMax(void (*cb_fun)(void)) {
    ccrMax_cb = cb_fun;
}

bool PWM::getOutput() {
    return cnt >= CCR;
}

void PWM::update(){
    if(cnt_up) cnt_up = (cnt++ < maxCnt);
    else cnt_up = (cnt-- <= 0);

    if(cnt == maxCnt) ccrMax_cb();
    if(cnt == 0) ccr0_cb();
}