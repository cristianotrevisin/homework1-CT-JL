# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--domain_length", "-l", help="domain length", type=float, default = 2.)
parser.add_argument("--number", "-n", help="number of particles per row", type = int, default = 16)
parser.add_argument("--radius", "-r", help="radius of the heat source", type = float, default = 1.)

args = parser.parse_args()

L = args.domain_length
N = args.number
R = args.radius

X = np.linspace(-L/2, L/2, N)
Y = np.linspace(-L/2, L/2, N)
xx,yy = np.meshgrid(X,Y)

z = np.zeros(N*N)

hh = np.zeros((N, N))

for i in range (N):
    for j in range(N):
        if xx[i,j]**2 + yy[i,j]**2 < R**2:
            hh[i,j] = 1
        else:
            hh[i,j] = 0

x = xx.flatten()
y = yy.flatten()
h = hh.flatten()

file_data = np.column_stack((x, y, z, z, z, z, z, z, z, z, z, h))
np.savetxt("gen_domain.csv", file_data, delimiter=" ")
        