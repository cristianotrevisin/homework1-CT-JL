#ifndef WRITESERIES_HH
#define WRITESERIES_HH
#include "DumperSeries.hh"
#include <string>
#include <iostream>

class WriteSeries : public DumperSeries {
    public:
    WriteSeries(Series & series, int maxiter, int freq);
    void setSeparator(std::string s) {separator = s;};
    void dump(std::ostream &os);

    private:
    int freq;
    int maxiter;
    std::string separator;
};

#endif