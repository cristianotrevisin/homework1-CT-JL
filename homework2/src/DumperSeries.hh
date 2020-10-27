#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH
#include "Series.hh"

class DumperSeries{

    public:
    virtual void dump();

    protected:
    
    Series & series;
};
#endif