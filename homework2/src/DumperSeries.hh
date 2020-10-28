#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH
#include "Series.hh"
#include <iostream>

class DumperSeries{

    public:
    DumperSeries(Series & series);
    //virtual void dump() = 0;
    virtual void dump(std::ostream &os) = 0;
    void setPrecision(unsigned int precision) { this->precision = precision; }

    //virtual ~DumperSeries();

    protected:
    
    Series & series;
    unsigned int precision;

};

inline std::ostream & operator <<(std::ostream & stream, DumperSeries & _this) {
  _this.dump(stream);
  return stream;
}
#endif