#include <cstdlib>
#include <cmath>
#include "Series.hh"
#include "ComputePi.hh"

double ComputePi::compute(unsigned int N){
    double pi2 = 0;
    for (unsigned int i = 0; i < N; ++i) {
        unsigned int k = N-i;
        pi2 += 1./(1.*k*k);
    }
    pi2 *= 6;
    return std::sqrt(pi2);
}

double getAnalyticPrediction(){
    return M_PI;
}
