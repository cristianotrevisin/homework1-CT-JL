#include "Series.hh"
#include "ComputeArithmetic.hh"
#include <cstdlib>
#include <iostream>

int main(int argc, char **charv){

    int N = atoi(charv[1]);

    ComputeArithmetic result;

    double a = result.compute(N);

    std::cout << a << std::endl;
    
}