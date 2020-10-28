#include "WriteSeries.hh"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

WriteSeries::WriteSeries(Series & series, int maxiter, int freq) : DumperSeries(series) {
    this->maxiter = maxiter;
    this->freq = freq;
    this->setSeparator(" ");
}

void WriteSeries::dump() {
    int nsteps = this->maxiter/this->freq;
    std::cout << nsteps << std::endl;

    std::ofstream myfile;
    myfile.open("example.txt", std::ios::out);
    myfile << "iter" << separator << "result" << separator << "error" << std::endl;
  
    for (int i = nsteps; i--> 1;){
        double res = this->series.compute(i); 

        double solution = this -> series.getAnalyticPrediction();
        myfile << i << separator << res << separator << abs(res-solution) << std::endl;   
    }
    myfile.close();
}