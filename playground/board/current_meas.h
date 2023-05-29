#ifndef _CURRENT_MEAS_
#define _CURRENT_MEAS_

class CurrentMeas {
    public:
        CurrentMeas(const double rm, const double Kopamp, const double offset);
        void setCurrent(const double val);
        double getMeasurement();
        void update();
    private:
        double r;
        double K;
        double off;
        double current;
        double measVal;
};

#endif