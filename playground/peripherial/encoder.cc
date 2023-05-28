#include "encoder.h"
#include <cmath>

Encoder::Encoder(const uint32_t cpr):cpr(cpr) {
    cnt = 0;
    pos = 0.0;
}

Encoder::~Encoder() {}

void Encoder::setPosition(const double pos_in_rad) {
    pos = pos_in_rad;
}

void Encoder::update() {
    cnt = pos / (2*M_PI) * (cpr-1);
}

uint32_t Encoder::getValue() {
    return cnt;
}