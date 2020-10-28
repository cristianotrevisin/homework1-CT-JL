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
        if (std::isnan(sol_ana))
            std::cout << "At iter " << i << " value series is " << std::setprecision(this->precision) << 
            res << "." << std::endl;
        else
            std::cout << "At iter " << i << " value series is " << std::setprecision(this->precision) << 
            res << " and convergence is " << abs(res-sol_ana) << "." << std::endl;
        
    }

}