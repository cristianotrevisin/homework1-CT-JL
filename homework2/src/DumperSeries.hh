#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH
#include "Series.hh"

class DumperSeries{

    public:
    DumperSeries(Series & series);
    virtual void dump() = 0;

    //virtual ~DumperSeries();

    protected:
    
    Series & series;
};
#endif