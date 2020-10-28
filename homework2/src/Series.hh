#ifndef SERIES_HH
#define SERIES_HH
#include <cmath>

class Series{
    /* Parent of the different serie: template to compute the term iteratively while conserving 
    memory of the current iteration value to save computer time */
    public: 
    virtual double compute(unsigned int N);
    virtual double getAnalyticPrediction() {return nan("");}
    virtual double computeTerm(unsigned int k) = 0;
    virtual ~Series() {};
    unsigned int current_index;
    double current_value;
};

#endif 