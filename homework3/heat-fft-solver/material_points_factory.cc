#include "material_points_factory.hh"
#include "compute_temperature.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> MaterialPointsFactory::createParticle() {
  return std::make_unique<MaterialPoint>();
}

/* -------------------------------------------------------------------------- */

SystemEvolution&
MaterialPointsFactory::createSimulation(const std::string& fname,
                                        Real timestep) {

  this->system_evolution =
      std::make_unique<SystemEvolution>(std::make_unique<System>());

  CsvReader reader(fname);
  reader.read(this->system_evolution->getSystem());

  // check if it is a square number
  auto N = this->system_evolution->getSystem().getNbParticles();
  int side = std::sqrt(N);
  if (side * side != N)
    throw std::runtime_error("number of particles is not square");

  /* Hardcoded values for parameters, we could imagine a Parameter class */
  /* Here for copper */
  Real rho = 8960;       /* mass density kg/m^3 */
  Real C = 385;          /* specific heat capacity J/(km*K)  */
  Real kappa = 284.1;    /* heat conductivity W/(m*K) */


  auto temperature = std::make_shared<ComputeTemperature>(timestep, rho, C, kappa);
  this->system_evolution->addCompute(temperature);

  return *system_evolution;
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& MaterialPointsFactory::getInstance() {
  if (not ParticlesFactoryInterface::factory)
    ParticlesFactoryInterface::factory = new MaterialPointsFactory;

  return *factory;
}

/* -------------------------------------------------------------------------- */
