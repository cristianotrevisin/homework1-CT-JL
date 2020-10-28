#ifndef SERIES_HH
#define SERIES_HH

class Series{
    public: 
   virtual double compute(unsigned int N) = 0;
    double getAnalyticPrediction();
};

#endif 