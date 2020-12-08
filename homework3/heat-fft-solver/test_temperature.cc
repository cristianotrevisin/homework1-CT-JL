#include "material_point.hh"
#include "system.hh"
#include "compute_temperature.hh"
#include <gtest/gtest.h>
#include "material_points_factory.hh"
#include "system_evolution.hh"
#include <vector>
#include "vector.hh"
#include <math.h>


/*****************************************************************/
// Fixture class
class CheckTemp : public ::testing::Test {
public:
  void SetUp() override {
    MaterialPointsFactory::getInstance(); 
    std::vector<MaterialPoint> testpts;
    UInt N = 8; // number of particles per line
    Real L = 2.; // length of the domain

    for (UInt i = 0; i < N; ++i){
        for (UInt j = 0; j < N; ++j){
            MaterialPoint p;

            p.getPosition()[0] = -L/2 + i*L/N;
            p.getPosition()[1] = -L/2 + j*L/N;
            p.getPosition()[2] = 0;
            

            testpts.push_back(p);

        }
    }

    for (auto& p : testpts) {

      system.addParticle(std::make_shared<MaterialPoint>(p));
    }
  }

  System system;
  UInt N;
  std::vector<MaterialPoint> testpts;
  Real L;
  UInt nsteps = 10;

};

/*****************************************************************/
TEST_F(CheckTemp,homogeneous_temperature){
    for (auto& p : testpts) {
      p.getTemperature() = 1.;
    }
    Real dt = 1;
    Real rho = 8960;      /* mass density kg/m^3 */
    Real C= 385;        /* specific heat capacity J/(km*K)  */
    Real kappa=284.1;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);

    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system);
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        std::cout << pt.getPosition() << std::endl;
        ASSERT_NEAR(pt.getTemperature(),1,1e-10);
      }
    }
}


/*****************************************************************/

TEST_F(CheckTemp,sinusoidal_heat){
    for (auto& p : testpts) {
      MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
      pt.getTemperature() = sin(2*M_PI*pt.getPosition()[0]/L);
      pt.getHeatRate() = (2*M_PI/L)*(2*M_PI/L)*sin(2*M_PI*pt.getPosition()[0]/L);
    }
    
    Real dt = 1;
    Real rho = 8960;      /* mass density kg/m^3 */
    Real C= 385;        /* specific heat capacity J/(km*K)  */
    Real kappa=284.1;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    
    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system);
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        Real x = pt.getPosition()[0];
        ASSERT_NEAR(pt.getTemperature(),sin(2*M_PI*x/L),1e-10);
      }
    }
}

/*****************************************************************/

TEST_F(CheckTemp,volumetric_heat){   
    for (auto&& p : testpts) {
      MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
      Vector xyz = pt.getPosition();
    
      if (xyz[0] <= -0.5)
        pt.getTemperature()=-xyz[0]-1;
      else if ((xyz[0] > -0.5) && (xyz[0] < 0.5))
        pt.getTemperature()=xyz[0];
      else 
        pt.getTemperature()=-xyz[0]+1;


      if (xyz[0] == 0.5)
        pt.getHeatRate() = 1.;
      else if (xyz[0] == -0.5)
        pt.getHeatRate() = -1.;
      else 
        pt.getHeatRate() = 0.;
    }
    
    // all values are here set to 0 to get the desired final solution
    Real dt = 1;
    Real rho = 1.;      /* mass density kg/m^3 */
    Real C= 1.;        /* specific heat capacity J/(km*K)  */
    Real kappa=1.;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    
    for (UInt i = 0; i < nsteps; ++i) {
      temperature->compute(system);
      for(auto& p : system){
        MaterialPoint & pt = dynamic_cast<MaterialPoint&>(p);
        Real x = pt.getPosition()[0];
        if (x <= -0.5)
          ASSERT_NEAR(pt.getTemperature(),-x-1,1e-10);
        else if ((x> -0.5) && (x < 0.5))
          ASSERT_NEAR(pt.getTemperature(),x,1e-10);
        else 
          ASSERT_NEAR(pt.getTemperature(),-x+1,1e-10);
      }
    } 
}

