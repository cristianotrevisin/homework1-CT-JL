#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_gravity.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"
#include "csv_writer.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project, submission of Cristiano Trevisin & Joseph Lemaitre";

  // bind the routines here
  py::class_<ParticlesFactoryInterface>(m, "ParticlesFactoryInterface")
    .def("getInstance",
        &ParticlesFactoryInterface::getInstance, 
        py::return_value_policy::reference)
    .def("createSimulation",
        (SystemEvolution & (ParticlesFactoryInterface::*)(const std::string &, Real))&ParticlesFactoryInterface::createSimulation,
        py::return_value_policy::reference)
    .def("createSimulation",
       (SystemEvolution & (ParticlesFactoryInterface::*)(const std::string &, Real,py::function))&ParticlesFactoryInterface::createSimulation, 
        py::return_value_policy::reference);
  /*
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(m, "MaterialPointsFactory")
    .def("getInstance", 
        &MaterialPointsFactory::getInstance, 
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real, py::function>(&MaterialPointsFactory::createSimulation),
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real>(&MaterialPointsFactory::createSimulation),
        py::return_value_policy::reference);
  
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(m, "PingPongBallsFactory")
    .def("getInstance", 
        &PingPongBallsFactory::getInstance, 
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real, py::function>(&PingPongBallsFactory::createSimulation), 
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real>(&PingPongBallsFactory::createSimulation), 
        py::return_value_policy::reference);
  
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(m, "PlanetsFactory")
    .def("getInstance", 
        &PlanetsFactory::getInstance, 
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real, py::function>(&PlanetsFactory::createSimulation), 
        py::return_value_policy::reference)
    .def("createSimulation",
        py::overload_cast<const std::string &, Real>(&PlanetsFactory::createSimulation), 
        py::return_value_policy::reference);
*/
  
}
