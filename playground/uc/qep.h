#ifndef _QEP_H_
#define _QEP_H_

#include <cstdint>

class QEP {
    public:
        void setMaxValue(const uint32_t val);
        void setValue(const uint32_t val);
        uint32_t getValue();
    private:
        uint32_t maxCnt;
        uint32_t cnt;
};

#endif