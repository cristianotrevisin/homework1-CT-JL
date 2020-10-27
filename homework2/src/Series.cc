#include "Series.hh"
#include <cstdlib>
#include <cmath>

class Series{

    public:

    virtual double compute(unsigned int N) = 0;

    virtual double getAnalyticPrediction() = nan();
};