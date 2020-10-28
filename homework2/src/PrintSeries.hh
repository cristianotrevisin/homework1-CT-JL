#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH
#include "DumperSeries.hh"

class PrintSeries : public DumperSeries {
    public:
    PrintSeries(Series & series, int maxiter, int freq);
    void dump();

    private:
    int freq;
    int maxiter;
};

#endif