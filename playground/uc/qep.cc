#include "qep.h"

void QEP::setMaxValue(const uint32_t val){
    maxCnt = val;
}

void QEP::setValue(const uint32_t val){
    cnt = val % maxCnt;
}

uint32_t QEP::getValue(){
    return cnt;
}