#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */
//! Compute one step of the transient heat equation
void ComputeTemperature::compute(System& system) {
    double rho = 1.0;
    double C = 1.0;
    double kappa = 1.0;
    double L = 1.0; //TODO
    double deltat = 1;

    int N = sqrt(system.getNbParticles());

    
    Matrix<complex> theta_n(N);
    Matrix<complex> hv(N);
     
    int i = 0;
    int j = 0;
    for (auto& par : system) {

        MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);

        std::cout << matpt.getTemperature() << " ";

        theta_n(i,j) = matpt.getTemperature();
        hv(i,j)    = matpt.getHeatRate();
        i++;
        if (i >= N){
            i = 0;
            j++;
            std::cout << std::endl;
        }
    }
    std::cout << "__________" << std::endl;

    Matrix<complex> thetah = FFT::transform(theta_n);
    Matrix<std::complex<int>> q_freq = FFT::computeFrequencies(N);
    Matrix<complex> hvh = FFT::transform(hv);
    
    std::complex<double> qfreq_ij;
    Matrix<complex> dthetah_over_dt(N);
    for (auto&& entry : index(dthetah_over_dt)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        // TODO Not L
        
        qfreq_ij = std::complex<double>(real(q_freq(i,j)), imag(q_freq(i,j)));
        //std::cout << q_freq(i,j) << qfreq_ij << real(q_freq(i,j)) << imag(q_freq(i,j)) << std::endl;
        val = (hvh(i,j) - kappa * thetah(i,j)  * qfreq_ij / (L*L)) / (rho * C);
        
    }

    Matrix<complex> dtheta_over_dt = FFT::itransform(dthetah_over_dt);

    i = 0; j = 0;
    for (auto& par : system) {

        MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);
        std::cout << theta_n(i,j) << "inc" << deltat*dtheta_over_dt(i,j) << std::endl;

        matpt.getTemperature() = std::real(theta_n(i,j) + deltat*dtheta_over_dt(i,j));
        i++;
        if (i >= N){
            i = 0;
            j++;
        }
    }
}

/* -------------------------------------------------------------------------- */
