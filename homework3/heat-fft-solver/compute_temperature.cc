#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {

    int size = sqrt(system.getNbParticles());
    std::cout << size << std::endl;

    /* Compute one step of the temperature */
    Matrix<complex> tetha;
    Matrix<complex> hv;

    for (auto& par : system) {
          MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);
          std::cout << matpt.getTemperature() << " "
          << matpt.getHeatRate()<< " -> " << matpt.getPosition() << "-" << matpt.getVelocity() <<
          matpt.getForce() << matpt.getMass() <<  std::endl;
    } // end for loop over particles

    /* Create a matrix from the particles */
    
    //Matrix<complex> m(N); 




}

/* -------------------------------------------------------------------------- */
