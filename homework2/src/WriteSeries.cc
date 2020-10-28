#include "WriteSeries.hh"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

WriteSeries::WriteSeries(Series & series, int maxiter, int freq) : DumperSeries(series) {
    this->maxiter = maxiter;
    this->freq = freq;
    this->setSeparator(" ");
}

void WriteSeries::dump(std::ostream &os) {

    double sol_ana = this->series.getAnalyticPrediction();

    os << "iter" << separator << "result" << separator << "error" << std::endl;   
    for (int i = 1; i <= this->maxiter; i += this->freq) {
        double res = this->series.compute(i); 
        os << i << separator << std::setprecision(this->precision) << res << separator << abs(res-sol_ana) << std::endl;   
    }

}
