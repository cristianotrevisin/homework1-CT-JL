#include "Series.hh"
#include "ComputeArithmetic.hh"
#include "ComputePi.hh"
#include "PrintSeries.hh"
#include "WriteSeries.hh"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **charv){

    int N = atoi(charv[1]);

    std::string series_method = charv[2];
    std::string dumper_method = charv[3];

    std::cout << dumper_method <<  std::endl;

    Series * result;

    if (series_method.compare("arithmetic")==0){
        result = new ComputeArithmetic;
        //ComputeArithmetic result;
        std::cout << "The calculated value of the series is " << result->compute(N) << std::endl;
    } else if (series_method.compare("pi")==0){
        //ComputePi result;
        result = new ComputePi;
        std::cout << "The estimated value of pi is " << result->compute(N) << std::endl;
    } else {
        std::cerr << "The chosen method " << series_method << " is not available!" << std::endl;
    }

    if (dumper_method.compare("print")==0){
        if (argc < 5) {
            unsigned int precision = 5;
        } else if (argc == 5) {
            unsigned int precision = atoi(charv[4]);
        }
        PrintSeries printserie(*result, 1000, 5);
        printserie.dump();
        std::cout << "dsds" << std::endl;
    } else if (dumper_method.compare("write")==0){
        if (argc < 5) {
            std::string separator = "space";
        } else if (argc == 5) {
            std::string separator = charv[4];
        }
        std::cout << "dewewew" << std::endl;
        WriteSeries writeserie(*result, 1000, 5);
        writeserie.dump();
        std::cout << "dsds" << std::endl;
    
    } else {
        std::cerr << "The chosen dumper method " << dumper_method << " is not available!" << std::endl;
    }



    delete result;

}