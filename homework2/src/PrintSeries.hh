#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH
#include "DumperSeries.hh"
#include <iostream>

class PrintSeries : public DumperSeries {
    public:
    PrintSeries(Series & series, int maxiter, int freq);
    void dump(std::ostream &os = std::cout);

    private:
    int freq;
    int maxiter;
};

#endif