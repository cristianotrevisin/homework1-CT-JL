"""
Generates the initial domain of particles. Takes as arguments:
    - domain length;
    - number of particles that should fit in this domain;
    - radius of the heat source.
"""

import numpy as np
import argparse

#parsing arguments
parser = argparse.ArgumentParser()
parser.add_argument("--domain_length", "-l", help="domain length", type=float, default = 2.)
parser.add_argument("--number", "-n", help="number of particles per row", type = int, default = 512)
parser.add_argument("--radius", "-r", help="radius of the heat source", type = float, default = 1.)

args = parser.parse_args()

L = args.domain_length
N = args.number
R = args.radius

# creating particle grid
X = np.linspace(-L/2, L/2, N)
Y = np.linspace(-L/2, L/2, N)
xx,yy = np.meshgrid(X,Y)
z = np.zeros(N*N)

# preallocating heat source vector
hh = np.zeros((N, N))

for i in range (N):
    for j in range(N):
        if xx[i,j]**2 + yy[i,j]**2 < R**2:
            hh[i,j] = 1
        else:
            hh[i,j] = 0

# getting flattened vector for easier storage and itemization of the particles
x = xx.flatten()
y = yy.flatten()
h = hh.flatten()

# assembling the particles in an array and saving in a csv
# arg position: x y z vx vy vz fx fy fz m T h
# where all but x, y, and h have value equal to 0
file_data = np.column_stack((x, y, z, z, z, z, z, z, z, z, z, h))
np.savetxt("gen_domain.csv", file_data, delimiter=" ")
        