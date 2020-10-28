#ifndef COMPUTEPI_HH
#define COMPUTEPI_HH

class ComputePi : public Series {
    /* Series that converge towards Pi */

    public:
    double compute(unsigned int N);
    double computeTerm(unsigned int k);
    double getAnalyticPrediction();
};

#endif 