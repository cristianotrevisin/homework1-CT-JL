#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {

    int N = sqrt(system.getNbParticles());

    /* Compute one step of the temperature */
    Matrix<complex> theta(N);
    Matrix<complex> hv(N);
     
 int i = 0;
 int j = 0;
    for (auto& par : system) {

        MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);

        std::cout << matpt.getTemperature() << " "
          << matpt.getHeatRate()<< " -> " << matpt.getPosition() << "-" << matpt.getVelocity() <<
          matpt.getForce() << matpt.getMass() <<  std::endl;
        std::cout << i << " " << j << std::endl;

        theta(i,j) = matpt.getTemperature();
        hv(i,j)    = matpt.getHeatRate();
        i++;
        if (i >= N){
            i = 0;
            j++;
        }
    }
    Matrix<complex> thetah = FFT::transform(theta);
    Matrix<std::complex<int>> q_freq = FFT::computeFrequencies(N);


    Matrix<complex> dthetah_over_dt(N);





    
     // end for loop over particles

    /* Create a matrix from the particles */
    
    //Matrix<complex> m(N); 




}

/* -------------------------------------------------------------------------- */
