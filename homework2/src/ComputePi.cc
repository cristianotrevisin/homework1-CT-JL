#include <cstdlib>
#include <cmath>
#include "Series.hh"
#include "ComputePi.hh"

double ComputePi::compute(unsigned int N){
    Series::compute(N);
    return std::sqrt(6.*this->current_value);
}

double ComputePi::computeTerm(unsigned int k){
    return 1./(1.*k*k);
}

double ComputePi::getAnalyticPrediction(){
    return M_PI;
}
