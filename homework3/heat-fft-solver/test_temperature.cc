#include "material_point.hh"
#include "system.hh"
#include "compute_temperature.hh"
#include <gtest/gtest.h>
#include "material_points_factory.hh"
#include "system_evolution.hh"
#include <vector>
#include "vector.hh"
#include <math.h>

#define TEST_TOLERANCE 1e-2


/*****************************************************************/
// Fixture class
class CheckTemp : public ::testing::Test {
  public:
    UInt N = 100; // number of particles per line
    Real L = 2.; // length of the domain


    void SetUp() override {
      MaterialPointsFactory::getInstance(); 
      std::vector<MaterialPoint> testpts; // to store the particles

      for (UInt i = 0; i < N; ++i){
          for (UInt j = 0; j < N; ++j){
              MaterialPoint p;
              p.getPosition()[0] = -L/2 + i*L/(N-1); // to place N evenly-spaced particles in a row
              p.getPosition()[1] = -L/2 + j*L/(N-1); // idem
              p.getPosition()[2] = 0; // z position is 0
              testpts.push_back(p); // pushing the created particle in the testpts vector
          }
    }

    for (auto& p : testpts) {
      system.addParticle(std::make_shared<MaterialPoint>(p)); // add generated particles to the system
    }
  }

  System system;
  UInt nsteps = 10;  /* number of steps to be tested. We test each step */
  Real dt = 0.0001;  /* timestep */
  // all values are here set to 1 to get the desired final solution
  Real  rho = 1.;      /* mass density kg/m^3 */
  Real  C=  1.;        /* specific heat capacity J/(km*K)  */
  Real  kappa=1.;    /* heat conductivity W/(m*K) */

};

/*****************************************************************/
TEST_F(CheckTemp,homogeneous_temperature){
    for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        pt.getTemperature() = 1.; // initial homogeneous temperature
    }

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa); // call computer

    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system); // iterate and compute each state
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        ASSERT_NEAR(pt.getTemperature(),1,TEST_TOLERANCE); // test at each iteration, for every particle
      }
    }
}


/*****************************************************************/

TEST_F(CheckTemp,sinusoidal_heat){
  // L = 2 since the domain spans Delta x = 2 and Delta y = 2
  // It is simplified in the equation (this makes it slightly faster as well)
    for(auto& p : system){
      MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
      pt.getTemperature() = sin(M_PI*pt.getPosition()[0]);  // initial & equilibrium temperature
      pt.getHeatRate() = (M_PI)*(M_PI)*sin(M_PI*pt.getPosition()[0]); // initial heat source
    }

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    
    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system);
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        Real x = pt.getPosition()[0];
        ASSERT_NEAR(pt.getTemperature(),sin(M_PI*x),TEST_TOLERANCE);
      }
    }
}

/*****************************************************************/
TEST_F(CheckTemp,volumetric_heat){   
    for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
      Vector xyz = pt.getPosition();
    
      // equilibrium temperature (should hold throughout)
      if (xyz[0] <= -0.5)
        pt.getTemperature()=-xyz[0]-1;
      else if ((xyz[0] > -0.5) && (xyz[0] <= 0.5))
        pt.getTemperature()=xyz[0];
      else 
        pt.getTemperature()=-xyz[0]+1;

      // initial heat source
      if (fabs(xyz[0] - 0.5) < L/(2*(N-1)))
        pt.getHeatRate() = 1.;
      else if (fabs(xyz[0] + 0.5) < L/(2*(N-1))) 
        pt.getHeatRate() = -1.;
      else
        pt.getHeatRate() = 0.;
    }

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    
    // test
    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system);
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        Real x = pt.getPosition()[0];
        if (x <= -0.5) {
          ASSERT_NEAR(pt.getTemperature(),-x-1,TEST_TOLERANCE);
          }
        else if ((x> -0.5) && (x < 0.5))
          ASSERT_NEAR(pt.getTemperature(),x,TEST_TOLERANCE);
        else 
          ASSERT_NEAR(pt.getTemperature(),-x+1,TEST_TOLERANCE);
      }
    } 
}