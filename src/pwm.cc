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

void Pwm::run(void (*cb_func)(void)){
    if(cnt_up) cnt_up = (cnt++ < maxCnt);
    else cnt_up = (cnt-- <= 0);

    if(cnt >= CCR) cb_func();
}