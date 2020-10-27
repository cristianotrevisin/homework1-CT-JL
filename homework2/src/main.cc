#include "Series.hh"
#include "ComputeArithmetic.hh"
#include "ComputePi.hh"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **charv){

    int N = atoi(charv[1]);

    std::string series_method = charv[2];

    if (series_method.compare("arithmetic")==0){
        ComputeArithmetic result;
        std::cout << "The calculated value of the series is " << result.compute(N) << std::endl;
    } else if (series_method.compare("pi")==0){
        ComputePi result;
        std::cout << "The estimated value of pi is " << result.compute(N) << std::endl;
    } else {
        std::cerr << "The chosen method " << series_method << " is not available!" << std::endl;
    }
    

    
}