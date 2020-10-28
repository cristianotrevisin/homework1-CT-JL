#include "PrintSeries.hh"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

PrintSeries::PrintSeries(Series & series, int maxiter, int freq) : DumperSeries(series) {
    this->maxiter = maxiter;
    this->freq = freq;
}

void PrintSeries::dump(std::ostream &os) {
    double sol_ana = this->series.getAnalyticPrediction();

    for (int i = 1; i <= this->maxiter; i += this->freq) {
        double res = this->series.compute(i); 
        os << "At iter " << i << ", value is " << std::setprecision(this->precision) << res; 
        if (not std::isnan(sol_ana))
            os << ", convergence is " << abs(res-sol_ana);
        os << "." << std::endl;
    }

}