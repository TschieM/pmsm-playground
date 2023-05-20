#ifndef _PWM_H
#define _PWM_H

#include <cstdint>

class Pwm {
    public:
        Pwm();
        ~Pwm();
        void setMaxCount(const uint32_t val);
        void setCompareReg(const uint32_t val);
        void run(void (*cb_func)(void));
    private:
        uint32_t maxCnt;
        uint32_t CCR;
        uint32_t cnt;
        bool cnt_up;
};

#endif