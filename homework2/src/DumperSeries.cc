#include "Series.hh"
#include "DumperSeries.hh"
#include <iostream>

DumperSeries::DumperSeries(Series & series) : series(series) {
    precision = 10;
}