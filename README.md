# Homework 1 by Cristiano Trevisin and Joseph Lemaitre
Repository containing the first homework of the course Scientific Programming for 
Engineers by Cristiano Trevisin and Joseph Lemaitre.

### System requirements
Needs python3.6+, with recent version of `numpy`, `scipy`, `matplotlib`. For exact version used by the maintainers,
please check file `requirements.txt`.

### Exercise 1

File `optimizer.py` uses the built-in method `scipy.optimize.minimize` to minimize a quadratic function. 
The script takes no arguments, as the function to optimize is set in the exercise handout. It outputs two files,
`optimize_BFGS.pdf` and `optimize_CG.pdf` which contains plot of the iterative path taken by 
two different methods (Broyden–Fletcher–Goldfarb–Shanno algorithm and Conjugate gradient) to locate the 
minima of the function.

It also display in the standart ouput the minizer of the quadratic function.

### Exercise 2

File `conjugate_gradient.py` implements manually the Conjugate Gradient algorithm, using einstein summation instead 
of built-in numpy operation.
It takes as arguments:

- `--filename`, `-f` : The path to file where system Ax=b is stored.
- `--plot`, `-p`: boolean if we output a file containing a plot of the iteration.
-`--initial_guess`, `-g`: The path to file where initial guess x0 is stored.
-`--tolerance` `-t` : Tolerance required for the solver, to compute only the necessary iterations.

### Example

It is possibe to run an example:

```
python conjugate_gradient.py -f example/Ab.csv
python optimizer.py
```