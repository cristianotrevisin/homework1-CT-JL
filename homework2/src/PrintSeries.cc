#include "DumperSeries.hh"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <iostream>

class PrintSeries : public DumperSeries {

    void dump(int maxiter, int freq) {
        int nsteps = maxiter/freq;
        

        for (unsigned int i = nsteps; i--> 1; ){
            //double res = DumperSeries::series.compute(i); // res = dumperserie.serie.compute()
            double res = this->series.compute(i); // res = self.serie.compute(i)
            
            try {
                double solution = this -> series.getAnalyticPrediction();
                std::cout << "At iter " << i << " value series is " << res << " and convergence is " << abs(res-solution) << " ." << std::endl;
            } catch (const std::exception & exce) {
                std::cout << "At iter " << i << " value series is " << res << " ." << std::endl;
            }

        }
    };
};