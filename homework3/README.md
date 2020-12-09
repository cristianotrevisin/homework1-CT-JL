# Homework 3 by Joseph Lemaitre and Cristiano Trevisin

## Instructions for running 
Please refer to the answer to question 4.6.

## Answers to questions
### Question 1 — Code Discovery
Class MaterialPoint inherits from class Particles and adds the following particle attributes: temperature and heat rate, class particles handling the common features to all types of particles. The other types of particles (Planet and PingPong) are organised similarly:  class Planet adds to the particle the attribute "Name" and class Ping Pong Ball adds to the particle the attribute  "radius".

Class Material Point Factory inherits from class ParticleFactoryInterface which is devoted to the creation of a new particle and of a new simulation from a given file. Class Material Point does so specifically for a given particle, by overriding the commands initialised in the mother class. Particles are then moved to the simulation and the system evolution is dumped.

Class matrix is a templated struct that organizes the particles in a matrix-like fashion, allowing straightforward computations of the heat flux through the FFT interface.

FFT is a class that handles the fast-Fourier-transform part of the code. It contain the calculators for the forward and backwards Fourier transform, which are handled in form of a complex matrix.


### Question 4.5
Adding a boundary conditions that forces particles outside the mentioned domain could be accomplished through:
1. Expanding the domain beyond the value of the radius R;
2. In the code, where the computations evolve, values outside the domain should progressively be assigned a temperature equal to zero. By choosing a reasonably small integration timestep dt, a null temperature on those points will be ensured. 

### Question 4.6
The simulation can be launched with the following command, after having compiled the executables:

```
./particles nsteps dump_freq input.csv particle_type timestep
```
where the arguments are:

* ```nsteps (int)``` are the number of integration steps;
* ```dump freq (int)``` controls the dumping frequency (i.e. the frequency at which the script will save to file the partial results);
* ```input.csv (str)``` is the name of the input file where the partices are located;
* ```particle_type (str)``` handles the type of particles; it should be equal to ```material_point``` for the purpose of this exercise;
* ```timestep (float)``` is the timestep of the integration.

The particles should be arranged through the included Python script ```generate_heat_source.py``` which will generate a initial condition as that referred to in Question 4.5. This script can be launched as 
```
python generate_heat_source.py -l 1 -n 512 -r 1
```
which will generate a 512x512 grid of particles in file `gen_domain.csv` that can be used as input of the main particles function. The main arguments are:
* ```-l``` the length of the domain (a side);
* ```-n``` the number of particles per row;
* ```-r``` the radius of the domain giving the initial heat source referred in Q4.5.

## Miscellaneous
### Test dynamic linking
````
otool -L test_fft
test_fft:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1292.0.0)
	/usr/local/opt/fftw/lib/libfftw3.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/local/opt/fftw/lib/libfftw3f.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 904.4.0)
```
