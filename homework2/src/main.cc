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

    /**
     * ./main max_iter serie_method dumper_method dump_freq (filename)
     * Arguments:
     * [int] max_iter : maximum number of iteration.
     * [str] serie_method : which serie to compute, either ari (arithmetic) or pi (converge towards pi).
     * [str] dumper_method : what to do with the computed serie: either write (in which case, provide filename
     * argument) or to the standart output.
     * [int] dump_freq : the frequency at which to dump the ouput to the dumper_method.
     * [str] filename :  if dumper_method == 'write', the filemane written. if the extension is .csv or .psv, use
     * the approriate separator (, or |), otherwise uses space as separator.
     **/

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
        
        std::cout << my_dumper;  /* or my_dumper.dump(std::cout); */
    } else if (dumper_method.compare("write")==0){
        WriteSeries my_dumper(*my_serie, max_iter, dump_freq);
        my_dumper.setPrecision(precision);

        /* infer separator from extension. */
        if(filename.substr(filename.find_last_of(".")) == ".csv")
            my_dumper.setSeparator(",");
        else if (filename.substr(filename.find_last_of(".")) == ".psv")
            my_dumper.setSeparator("|");

        std::ofstream my_file;
        my_file.open(filename, std::ios::out);
        my_file << my_dumper;  /*or my_dumper.dump(my_file); */
        my_file.close();
    } else {
        std::cerr << "The chosen dumper method " << dumper_method << " is not available!" << std::endl;
        exit(1);
    }

    delete my_serie;
}