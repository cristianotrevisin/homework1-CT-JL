#include <cstdlib>
#include <cmath>
#include "Series.hh"

class ComputePi : public Series {

    public: 

    double compute(unsigned int N){
        double pi2 = 0;
        for (int i = 0; i <= N; ++i) {
            unsigned int k = N-i;
            pi2 += 1./(1.*k*k);
        }
        pi2 *= 6;
        return std::sqrt(pi2);
    };

};
