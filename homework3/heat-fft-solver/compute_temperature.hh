#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {
public:
  // constructor
  ComputeTemperature(Real timestep, Real rho, Real C, Real kappa);
  //! Penalty contact implementation
  void compute(System& system) override;

  void setDeltaT(Real dt);
private:
  Real dt;       /* integration time step */
  Real rho;      /* mass density */
  Real C;        /* specific heat capacity */
  Real kappa;    /* heat conductivity */

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
