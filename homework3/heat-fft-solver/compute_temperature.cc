#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>
#include <limits>

ComputeTemperature::ComputeTemperature(Real dt, Real rho, Real C, Real kappa) 
                              : dt(dt), rho(rho), C(C), kappa(kappa) {}

void ComputeTemperature::setDeltaT(Real dt) { this->dt = dt; }

/* -------------------------------------------------------------------------- */
//! Compute one step of the transient heat equation
void ComputeTemperature::compute(System& system) {
    int N = sqrt(system.getNbParticles());

    Matrix<complex> theta_n(N);
    Matrix<complex> hv(N);
     
    /* Get the system into matrices to help the fourier transform */
    int i = 0;
    int j = 0;
    /* We assume the system to be a rectangular grid with a square number of MaterialPoint */
    Real max_x = std::numeric_limits<Real>::min();
    Real min_x = std::numeric_limits<Real>::max();
    Real max_y = std::numeric_limits<Real>::min();
    Real min_y = std::numeric_limits<Real>::max();
    for (auto& par : system) {

        MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);

        double ptx = matpt.getPosition()[0];
        double pty =  matpt.getPosition()[1];
        min_x = std::min(min_x, ptx);
        min_y = std::min(min_x, pty);
        max_x = std::max(max_x, ptx);
        max_y = std::max(max_x, pty);

        theta_n(i,j) = matpt.getTemperature();
        hv(i,j)      = matpt.getHeatRate();
        std::cout << matpt.getTemperature() << " ";
        
        i++;
        if (i >= N){
            i = 0;
            j++;
            std::cout << std::endl;
        }
    }
    std::cout << "__________" << std::endl;

    /* Find the lenght of the system in the same units */
    Real Lx = max_x - min_x;
    Real Ly = max_y - min_y;

    /* Space fourier transform and unscalled frequencies */
    Matrix<complex> thetah = FFT::transform(theta_n);
    Matrix<std::complex<int>> q_freq = FFT::computeFrequencies(N);
    Matrix<complex> hvh = FFT::transform(hv);

    /* Compute, for each particle, it's Delta in time in fourier space */
    std::complex<double> qfreq_ij;
    Matrix<complex> dthetah_over_dt(N);
    for (auto&& entry : index(dthetah_over_dt)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        
        qfreq_ij = std::complex<double>(real(q_freq(i,j)), imag(q_freq(i,j)));
        Real q_x = (2*M_PI/Lx)*q_freq(i,j).real();
        Real q_y = (2*M_PI/Ly)*q_freq(i,j).imag();

        val = (hvh(i,j) - kappa * thetah(i,j)  * (q_x*q_x + q_y*q_y)) / (rho * C);
        
    }

    /* inverse transform of the delta of temperature over time */
    Matrix<complex> dtheta_over_dt = FFT::itransform(dthetah_over_dt);

    /* perform the forward euler scheme and write the new system state */
    i = 0; j = 0;
    for (auto& par : system) {
        MaterialPoint & matpt = dynamic_cast<MaterialPoint&>(par);
        matpt.getTemperature() = std::real(theta_n(i,j) + dt*dtheta_over_dt(i,j));
        i++;
        if (i >= N){
            i = 0;
            j++;
        }
    }
}

/* -------------------------------------------------------------------------- */
