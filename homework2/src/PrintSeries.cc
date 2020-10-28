#include "PrintSeries.hh"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>

PrintSeries::PrintSeries(Series & series, int maxiter, int freq) : DumperSeries(series) {
    this->maxiter = maxiter;
    this->freq = freq;
}

void PrintSeries::dump(std::ostream &os) {
    int nsteps = this->maxiter/this->freq;
    std::cout << nsteps << std::endl;
    for (int i = nsteps; i--> 1;){
        double res = this->series.compute(i); 
        try {
            double solution = this -> series.getAnalyticPrediction();
            std::cout << "At iter " << i << " value series is " << res << " and convergence is " << abs(res-solution) << " ." << std::endl;
        } catch (const std::exception & exce) {
            std::cout << "At iter " << i << " value series is " << res << " ." << std::endl;
        }
    }
}