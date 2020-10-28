#ifndef SERIES_HH
#define SERIES_HH
#include <cmath>
class Series{
    public: 
    virtual double compute(unsigned int N) = 0;
    virtual double getAnalyticPrediction() {return nan("");}
};

#endif 