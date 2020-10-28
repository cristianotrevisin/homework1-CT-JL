#ifndef WRITESERIES_HH
#define WRITESERIES_HH
#include "DumperSeries.hh"

class WriteSeries : public DumperSeries {
    public:
    WriteSeries(Series & series, int maxiter, int freq);
    void dump();

    private:
    int freq;
    int maxiter;
};

#endif