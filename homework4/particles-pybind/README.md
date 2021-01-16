# Homework 4 by Cristino Trevisin and Joseph Lemaitre

## Exercise 1.2
`ParticleFactory::createSimulation` is overloaded, i.e calls different methods depending on call argument. In this case, it is use in a nested, russian doll kind of way: the method with signature `Func func` set the compute to the provided function and then call the barebone `createSimulation`.