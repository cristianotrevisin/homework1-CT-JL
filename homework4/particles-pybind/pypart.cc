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
    /* we didn't manage to get something worthwile using py::overload_cast and as https://piazza.com/class/kenurrq73ut30c?cid=45_f1 this worked for us */
    .def("createSimulation",
        (SystemEvolution & (ParticlesFactoryInterface::*)(const std::string &, Real))(&ParticlesFactoryInterface::createSimulation),
        py::return_value_policy::reference)
    .def("createSimulation",
       (SystemEvolution & (ParticlesFactoryInterface::*)(const std::string &, Real,py::function))(&ParticlesFactoryInterface::createSimulation), 
        py::return_value_policy::reference)
    .def_property_readonly("system_evolution", &ParticlesFactoryInterface::getSystemEvolution);
  
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(m, "MaterialPointsFactory")
    .def("getInstance", 
        &MaterialPointsFactory::getInstance, 
        py::return_value_policy::reference);
  
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(m, "PingPongBallsFactory")
    .def("getInstance", 
        &PingPongBallsFactory::getInstance, 
        py::return_value_policy::reference);
  
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(m, "PlanetsFactory")
    .def("getInstance", 
        &PlanetsFactory::getInstance, 
        py::return_value_policy::reference);


  py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute");
  py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(m, "ComputeInteraction");
  
  py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(m, "ComputeGravity")
    .def(py::init<>())
    .def("setG", &ComputeGravity::setG);
  
  py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(m, "ComputeTemperature")
    .def_property_readonly("conductivity", &ComputeTemperature::getConductivity)
    .def_property_readonly("L", &ComputeTemperature::getL)
    .def_property_readonly("capacity", &ComputeTemperature::getCapacity)
    .def_property_readonly("density", &ComputeTemperature::getDensity)
    .def_property_readonly("deltat", &ComputeTemperature::getDeltat);

  py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(m, "ComputeVerletIntegration")
    .def(py::init<Real>())
    .def("addInteraction", &ComputeVerletIntegration::addInteraction);;

	py::class_<CsvWriter>(m, "CsvWriter")
      .def(py::init<const std::string&>())
      .def("write", &CsvWriter::write);

  py::class_<SystemEvolution>(m, "SystemEvolution")
    .def("getSystem", &SystemEvolution::getSystem)
    .def("addCompute", &SystemEvolution::addCompute)
    .def("evolve", &SystemEvolution::evolve)
    .def("setDumpFreq", &SystemEvolution::setDumpFreq)
    .def("setNSteps", &SystemEvolution::setNSteps);

    py::class_<System>(m, "System");

}
