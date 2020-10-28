#include "Series.hh"
#include "ComputeArithmetic.hh"
#include "ComputePi.hh"
#include "PrintSeries.hh"
#include "WriteSeries.hh"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main(int argc, char **charv){

    std::string series_method;
    std::string dumper_method;
    std::string filename;
    int max_iter, dump_freq;
    int precision = 5;

    /* Concatenate arguments */
    std::stringstream ss;
    for (int i=1; i < argc; i++) {
        ss << charv[i] << " ";
    }
    /* Parse arguments */
    ss >> max_iter >> series_method >> dumper_method >> dump_freq >> filename;
    
    Series * my_serie;
    //DumperSeries * my_dumper;

    if (series_method.compare("ari")==0){
        my_serie = new ComputeArithmetic;
    } else if (series_method.compare("pi")==0){
        my_serie = new ComputePi;
    } else {
        std::cerr << "The chosen method " << series_method << " is not available!" << std::endl;
        exit(1);
    }

    if (dumper_method.compare("print")==0){
        PrintSeries my_dumper(*my_serie, max_iter, dump_freq);
        my_dumper.setPrecision(precision);
        my_dumper.dump(std::cout);
    } else if (dumper_method.compare("write")==0){
        WriteSeries my_dumper(*my_serie, max_iter, dump_freq);

        /* infer separator from extension. */
        if(filename.substr(filename.find_last_of(".")) == ".csv")
            my_dumper.setSeparator(",");
        else if (filename.substr(filename.find_last_of(".")) == ".psv")
            my_dumper.setSeparator("|");
        my_dumper.setPrecision(precision);

        std::ofstream my_file;
        my_file.open(filename, std::ios::out);
        my_dumper.dump(my_file);
        my_file.close();
        
    } else {
        std::cerr << "The chosen dumper method " << dumper_method << " is not available!" << std::endl;
        exit(1);
    }


    //delete my_dumper;
    delete my_serie;

}