# Homework 3 by Joseph Lemaitre and Cristiano Trevisin

## Instructions for running 

## Answers to questions
### Question 1 — Code Discovery
Class MaterialPoint inherits from class Particles and adds the following particle attributes: temperature and heat rate, class particles handling the common features to all types of particles. The other types of particles (Planet and PingPong) are organised similarly:  class Planet adds to the particle the attribute "Name" and class Ping Pong Ball adds to the particle the attribute  "radius".

Class Material Point Factory inherits from class ParticleFactoryInterface which is devoted to the creation of a new particle and of a new simulation from a given file. Class Material Point does so specifically for a given particle, by overriding the commands initialised in the mother class. Particles are then moved to the simulation and the system evolution is dumped.

Class matrix is a templated class that first introduces the iterator on the several generated particles


### Question 4.5

### Question 4.6



## Test dynamic linking
````
otool -L test_fft
test_fft:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1292.0.0)
	/usr/local/opt/fftw/lib/libfftw3.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/local/opt/fftw/lib/libfftw3f.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 904.4.0)
```
