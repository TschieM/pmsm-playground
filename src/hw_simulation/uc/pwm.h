#ifndef _PWM_H_
#define _PWM_H_

#include <cstdint>

class Pwm {
    public:
        Pwm();
        ~Pwm();
        void setMaxCount(const uint32_t val);
        void setCompareReg(const uint32_t val);
        void setCallBackAtCCR0(void (*cb_fun)(void));
        void setCallBackAtCCRMax(void (*cb_fun)(void));
        void run(void (*cb_func_high)(void), void (*cb_func_low)(void));
    private:
        uint32_t maxCnt;
        uint32_t CCR;
        uint32_t cnt;
        bool cnt_up;
        void (*ccr0_cb)(void);
        void (*ccrMax_cb)(void);
};

#endif