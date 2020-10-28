#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH
#include "Series.hh"

class DumperSeries{

    public:
    virtual void dump() = 0;

    protected:
    
    Series & series;
};
#endif