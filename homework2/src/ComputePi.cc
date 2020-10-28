#include <cstdlib>
#include <cmath>
#include "Series.hh"
#include "ComputePi.hh"

double ComputePi::compute(unsigned int N){
    double pi2 = 0;
    /* inverse loop for numerical errors */
    for (unsigned int i = N; i > 0; --i) {
        pi2 += 1./(1.*i*i);
    }
    pi2 *= 6;
    return std::sqrt(pi2);
}

double getAnalyticPrediction(){
    return M_PI;
}
