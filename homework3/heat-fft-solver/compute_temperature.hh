#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {


public:
  // constructor
  ComputeTemperature(Real timestep);
  //! Penalty contact implementation
  void compute(System& system) override;

  void setDeltaT(Real dt);
private:
  Real dt;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
