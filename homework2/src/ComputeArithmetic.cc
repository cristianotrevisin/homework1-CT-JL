#include <cstdlib>
#include <cmath>
#include "Series.hh"
#include "ComputeArithmetic.hh"

double ComputeArithmetic::compute(unsigned int N){
        double res = 0;
        for (int i = 0; i <= N; ++i) {
            res += i;
        }
        return res;
}