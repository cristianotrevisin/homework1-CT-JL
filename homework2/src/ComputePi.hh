#ifndef COMPUTEPI_HH
#define COMPUTEPI_HH

class ComputePi : public Series {

    public:
    double compute(unsigned int N);
    double getAnalyticPrediction();

};

#endif 