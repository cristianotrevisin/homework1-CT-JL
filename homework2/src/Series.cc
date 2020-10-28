#include "Series.hh"
#include <cstdlib>

double Series::compute(unsigned int N) {
    if (this->current_index <= N) {
        N = N - this->current_index;
    }
    else{
        this->current_index = 0;
        this->current_value = 0;
    }
    for (unsigned int k = 0; k < N; ++k) {
        this->current_index += 1;
        this->current_value += this->computeTerm(this->current_index);
    }
    return this->current_value;
}