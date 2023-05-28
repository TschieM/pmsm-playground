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

bool Pwm::getOutput() {
    return cnt >= CCR;
}

void Pwm::update(){
    if(cnt_up) cnt_up = (cnt++ < maxCnt);
    else cnt_up = (cnt-- <= 0);

    if(cnt == maxCnt) ccrMax_cb();
    if(cnt == 0) ccr0_cb();
}