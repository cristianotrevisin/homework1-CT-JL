# Homework 4 by Cristiano Trevisin and Joseph Lemaitre

## Instructions for running the scripts
### Main script
To run the main script and generate the dumps, the script should hit the following commands on the terminal:

```
mkdir build
cd build
mkdir dumps
cmake .. && make && python3.8 main.py nb_steps freq filename particle_type timestep
```
where `nb_steps` is the number of steps to simulate, `freq` is the frequency at which dumps should be reported, `particle_type` is the kind of particle solver (in this case we are using the `planet` variant) and `timestep` is the temporal length between steps. To generate a simulation of 1 year with 365 steps (as requested by exercise 4.2), we recommmend to hit the following command, after `make`:
```
python3.8 main.py 365 1 ../init.csv planet 1
```

### Optimiser
The optimiser is aimed at correcting the initial velocity for Mercury in the `init.csv`file to yield the correct position. To do this, a scaling factor that multiplies the magnitude of the initial velocities (in the three directions) is introduced and a minimiser function from the package Scipy is used to calculate the correct vector of this scaling parameter. After launching the optimiser function, the user will find in the directory the plot of the scipy chain, the file with the corrected initial velocity `init_scaled.csv` and on screen the value of the scaling parameter. To launch the optimiser, the end user should hit the following commands:
```
mkdir build
cd build
mkdir dumps
cmake .. && make && python3.8 optimiser.py filename nb_steps freq timestep planet_name
```
or, simply:
```
python3.8 optimiser.py ../init.csv 365 1 1 mercury
```
Since the optimiser is written to correct the initial velocity for a planet, we deemed not necessary to grant the end-user the option to choose the desired particle solver and the options `ping_pong` and `material_point` are disabled. We allow, however, tweaking, by letting the user choose the name of the planet to optimise. In the spirit of the exercise, we set the default value for `mercury`, as we did for the number of steps `nb_steps = 365`, the frequency `freq = 1` and the timestep `timestep = 1`. If the user so wishes, a simpler command can be hit:
```
python3.8 optimiser.py
```
The optimiser script is written using a class scheme to allow better factorisation and management of the arguments. For this reason, the function may have slightly different input to those requested in the project, as fundamental arguments (i.e. frequency, number of steps, pianet name, and timestep) are managed as objects of the class. 

## Answers to questions
### Exercise 1.2
`ParticleFactory::createSimulation` is overloaded, i.e calls different methods depending on call argument. In this case, it is used in a nested, russian dolls kind of way: the method with signature `Func func` sets the compute to the provided function and then calls the barebone `createSimulation`.

### Exercice 2.2
We ensure correct management of the `Compute` object using shared pointers as object holder. It is a type of CPP smartpointers that allows objects to be passed beyond the scope they are defined for, but counts the references and deletes the object if there is no more references attached to it, so we avoid memory leak or deleting twice the same pointer.
