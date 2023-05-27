#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <cstdint>

class Encoder {
    public:
        Encoder(const uint32_t cpr);
        ~Encoder();
        void setPosition(const double pos_in_rad);
        void update();
        uint32_t getValue();
    private:
        uint32_t cpr;
        uint32_t cnt;
        double pos;
};

#endif