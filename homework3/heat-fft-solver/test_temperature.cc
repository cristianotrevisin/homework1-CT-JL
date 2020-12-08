#include "material_point.hh"
#include "system.hh"
#include "compute_temperature.hh"
#include <gtest/gtest.h>
#include "material_points_factory.hh"
#include <vector>
#include "vector.hh"


/*****************************************************************/
// Fixture class
class CheckTemp : public ::testing::Test {
public:
  void SetUp() override {
    MaterialPointsFactory::getInstance(); 
    std::vector<MaterialPoint> testpts;
    UInt N = 20; // number of particles per line
    Real L = 2.; // length of the domain

    for (unsigned int i = 0; i < N; ++i){
        for (unsigned int j = 0; i < N; ++i){
            MaterialPoint p;
            Vector xyz;
            xyz[0] = -L/2 + i/N*L;
            xyz[1] = -L/2 + j/N*L;
            xyz[2] = 0;
            p.getPosition() = xyz;

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

};

/*****************************************************************/
TEST_F(CheckTemp,homogeneous_temperature){
    for (auto& p : testpts) {
      MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
      pt.getTemperature() = 1.;
    }
    Real dt = 1;
    Real rho = 8960;      /* mass density kg/m^3 */
    Real C= 385;        /* specific heat capacity J/(km*K)  */
    Real kappa=284.1;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    temperature->compute(system);

    for (auto& p : testpts) {
        MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);

        ASSERT_NEAR(pt.getTemperature(),1,1e-10);
    }
}

/*****************************************************************/

TEST_F(CheckTemp,sinusoidal_heat){
    for (auto& p : testpts) {
      MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
      Vector xyz = pt.getPosition();
      pt.getTemperature() = 1.;
      pt.getHeatRate() = (2*M_PI/L)*(2*M_PI/L)*sin(2*M_PI*xyz[0]/L);
    }
    std::cout << "allocation passed" << std::endl;
    Real dt = 1;
    Real rho = 8960;      /* mass density kg/m^3 */
    Real C= 385;        /* specific heat capacity J/(km*K)  */
    Real kappa=284.1;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    std::cout << "here" << std::endl;
    temperature->compute(system);
    std::cout << "computation passed" << std::endl;
    for (auto& p : testpts) {
        MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
        Vector xyz = pt.getPosition();
        ASSERT_NEAR(pt.getTemperature(),sin(2*M_PI*xyz[0]/L),1e-10);

    }
}

/*****************************************************************/

TEST_F(CheckTemp,volumetric_heat){
    std::cout << "allocation started" << std::endl;
    for (auto& p : testpts) {
      MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
      Vector xyz = pt.getPosition();
      pt.getTemperature() = 1.;

      if (xyz[0] == 0.5)
        pt.getHeatRate() = 1.;
      else if (xyz[0] == -0.5)
        pt.getHeatRate() = -1.;
      else 
        pt.getHeatRate() = 0.;
    }
    std::cout << "allocation passed" << std::endl;
    Real dt = 1;
    Real rho = 8960;      /* mass density kg/m^3 */
    Real C= 385;        /* specific heat capacity J/(km*K)  */
    Real kappa=284.1;    /* heat conductivity W/(m*K) */

    auto temperature = std::make_shared<ComputeTemperature>(dt, rho, C, kappa);
    temperature->compute(system);
    std::cout << "computation passed" << std::endl;  
    for (auto& p : testpts) {
        MaterialPoint & pt= dynamic_cast<MaterialPoint&>(p);
        Vector xyz = pt.getPosition();

        if (xyz[0] <= -0.5)
          ASSERT_NEAR(pt.getTemperature(),-xyz[0]-1,1e-10);
        else if ((xyz[0] > -0.5) && (xyz[0] < 0.5))
          ASSERT_NEAR(pt.getTemperature(),xyz[0],1e-10);
        else 
          ASSERT_NEAR(pt.getTemperature(),-xyz[0]+1,1e-10);

    }
}