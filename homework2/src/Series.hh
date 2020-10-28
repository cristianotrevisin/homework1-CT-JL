#ifndef SERIES_HH
#define SERIES_HH
#include <cmath>

class Series{
    public: 
    virtual double compute(unsigned int N);
    virtual double getAnalyticPrediction() {return nan("");}
    virtual double computeTerm(unsigned int k) = 0;
    unsigned int current_index;
    double current_value;
};

#endif 