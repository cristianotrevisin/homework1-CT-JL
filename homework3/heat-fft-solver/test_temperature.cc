#include "compute_temperature.hh"
#include <gtest/gtest.h>
#include "material_points_factory.hh"

/*****************************************************************/
TEST_F(InitialHomogeneousTemperature,iht){
    UInt N = 20; // number of particles per line
    float L = 2.; // length of the domain

    for (unsigned int i = 0; i < N; ++i){
        for (unsigned int j = 0; i < N; ++i){
            MaterialPoint p;
            std::vector<float> xyz;
            xyz[0] = -L/2 + i/N*L;
            xyz[1] = -L/2 + j/N*L;
            xyz[2] = 0;
            p.getPosition(xzy);
            p.getVelocity() = 0;
            p.getForce() = 0;
            p.getMass() = 0;
            p.getTemperature() = 1;
            p.getHeatRate() = 0;

            

        }
    }

}

/*****************************************************************/

TEST_F(VolumetricHeatSource1,vhs1){
    
}

/*****************************************************************/

TEST_F(VolumetricHeatSource1,vhs1){
    
}