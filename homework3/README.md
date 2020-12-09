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
Adding a boundary conditions that forces particles outside the mentioned domain could be accomplished through expanding the domain beyond the value of the radius R (say, to 2R). This condition has been tested.
FFT will indeed apply periodic boundary conditions and an expanded domain will allow this behaviour to correctly integrate the required boundary condition in the computations.

### Question 4.6
To obtain a simulation producing dumps which can be observed through Paraview, the user should follow the hereunder procedure:
1. Generate an appropriate initial condition file. This will contain a list of particles (that should be a square number!) with their position (3D), velocity field (3D), force field (3D), mass, initial temperature and heat flux. If the end user desires to apply the conditions referred to in question 4.6, the included Python script ```generate_heat_source.py``` should be used. This script can be launched as 
```
python generate_heat_source.py -l 2 -n 512 -r 1
```
which will generate a 512x512 grid of particles in file `gen_domain.csv` that can be used as input of the main particles function (see below). The main arguments are:
* ```-l``` the length of the domain (a side);
* ```-n``` the number of particles per row;
* ```-r``` the radius of the domain giving the initial heat source referred to in Q4.5.

2. Secondly, a build folder should be made and selected:
```
mkdir build
cd build
```
and then the following commands will build the executable:
```
cmake ..
make
mkdir dumps
```

3. The simulation can be launched with the following command, after having compiled the executables:

```
./particles nsteps dump_freq input.csv particle_type timestep
```
where the arguments are:

* ```nsteps (int)``` are the number of integration steps;
* ```dump freq (int)``` controls the dumping frequency (i.e. the frequency at which the script will save to file the partial results);
* ```input.csv (str)``` is the name of the input file where the partices are located (`gen_domain.csv` if the user wishes to apply the conditions of question 4.6);
* ```particle_type (str)``` handles the type of particles; it should be equal to ```material_point``` for the purpose of this exercise;
* ```timestep (float)``` is the timestep of the integration.

An example is:
```
./particles 10000 100 ../gen_domain.csv material_point .31
```

4. The user will then be able to visualise with Paraview. To do so, the software should be launched and the user should navigate to `dumps/`. There, the dataset should be opened through the csv reader (please choose no header, and space as delimiter). 
To create a visualisation of the data, go to Filters/Alphabetical/Table To Points. Set columns 0, 1, 2 as X, Y, Z (or set Paraview as 2D) and hit Apply. You should  now be able to choose a column for color. We recommend column 13: temp or column 14: heat. By clicking on play, it should animate and time the integration of the transient heat equation.

NB: For the FFTW package to be included and linked to the executable, the relative option in the `CMakeLists.txt` (line 9) should be set as: `ON`. The GoogleTest package should also be included in the repository beforehand, through the command:
```
git submodule add https://github.com/google/googletest.git googletest

```
Tests can be ran after `make` by hitting `.\test_fft` for the Fast-Fourier Transform or by typing `.\test_temperature` for the tests on the `computeTemperature.cc` class.

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
