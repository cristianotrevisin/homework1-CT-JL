# Homework 4 by Cristino Trevisin and Joseph Lemaitre

## Instructions for running the scripts
To run the main script and generate the dumps, the script should hit the following commands on the terminal:

````
mkdir build
cd build
mkdir dumps
cmake .. && make && python3.8 main.py nb_steps freq filename particle_type timestep
```
where `nb_steps` is the number of steps to simulate, `freq` is the frequency at which dumps should be reported, `particle_type` is the kind of particle solver (this is optimized for the `planet` variant) and `timestep` is the temporal length between steps. To generate a simulation of 1 year with 365 steps, we recommmend to hit the following command, after `make`:
````
python3.8 main.py 365 1 ../init.csv planet 1
```

## Exercise 1.2
`ParticleFactory::createSimulation` is overloaded, i.e calls different methods depending on call argument. In this case, it is use in a nested, russian doll kind of way: the method with signature `Func func` set the compute to the provided function and then call the barebone `createSimulation`.

## Exercice 2.2
we ensure correct management of the `Compute` object using shared pointers as object holder. It's a type of CPP smartpointers that allow object to be passed beyond the scope their defined, but count the references and delete the object if there is no more references attached to it, so we avoid memory leak or deleting twice the same pointer.
