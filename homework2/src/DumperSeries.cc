#include "Series.hh"
#include "DumperSeries.hh"

class DumperSeries{

    public:
    virtual void dump() = 0;

    protected:

    Series & series;
};