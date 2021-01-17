#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 13 11:30:23 2021

@author: cristiano
"""

import numpy as np
import os
import pandas as pd
import glob
import scipy.optimize.optimize as soo
import argparse
import matplotlib.pyplot as plt
import pypart
from pypart import MaterialPointsFactory, ParticlesFactoryInterface
from pypart import PlanetsFactory
from pypart import CsvWriter
from pypart import ComputeGravity
from pypart import ComputeVerletIntegration



def readPositions(planet_name,directory):
    filelist = sorted(glob.glob(os.path.join(directory, './step-*.csv')))
    if len(filelist) != 365:
        raise Exception('The length of the input datafile is not 365!')
    trajectory = np.empty((0,3), float)
    for file in filelist:
        a = pd.read_csv(file, sep = '\s',header = None, engine='python')
        if a.iloc[0,0] == '#X':
            a = pd.read_csv(file, sep = '\s',header=0,engine='python')
        planet_position = a[a.iloc[:,-1]==planet_name].iloc[:,0:3].to_numpy()
        trajectory = np.append(trajectory, planet_position, axis = 0)
    return trajectory
            
def computeError(positions,positions_ref):
    SSR = 0
    for i in range(365):
        for j in range(3):
            SSR += (positions[i,j]-positions_ref[i,j])**2
    return np.sqrt(SSR)

def generateInput(scale,planet_name,input_filename,output_filename):
    input_df = pd.read_csv(input_filename, sep = '\s',header=0,engine='python')
    input_df.loc[input_df.name == planet_name, ['VX','VY','VZ']] *= scale
    input_df.to_csv(output_filename,header=True,index_label = False, sep = ' ')
    
def launchParticles(input_file,nb_steps,freq,timestep):
    PlanetsFactory.getInstance()
    factory = ParticlesFactoryInterface.getInstance()

    def createComputes(self, timestep):  
        try:
            compute_grav = ComputeGravity()
            compute_verlet = ComputeVerletIntegration(timestep)
    
            G = 6.67384e-11 # m^3 * kg^-1 * s^-2
            UA = 149597870.700 # km
            earth_mass = 5.97219e24 # kg
            G /= (UA * 1e3)**3 # UA^3 * kg^-1 * s^-2
            G *= earth_mass    # UA^3 * earth_mass^-1 * s^-2
            G *= (60*60*24)**2 # UA^3 * earth_mass^-1 * day^-2
    
            compute_grav.setG(G)
            compute_verlet.addInteraction(compute_grav)
            self.system_evolution.addCompute(compute_verlet)
        
        except Exception as e:
            help(compute_grav)
            raise e
    
    evol = factory.createSimulation(filename, timestep, createComputes)

    dumper = CsvWriter("out.csv")
    dumper.write(evol.getSystem())
    
    evol.setNSteps(nb_steps)
    evol.setDumpFreq(freq)
    evol.evolve()
    
def runAndComputeError(scale,planet_name,input_file,nb_steps,freq,timestep):
    output_filename = 'init_scaled.csv'
    generateInput(scale,planet_name,input_file,output_filename)
    launchParticles(output_filename, nb_steps, freq,timestep)
    positions = readPositions(planet_name, os.getcwd() + '/dumps')
    positions_ref = readPositions(planet_name,  '../trajectories')
    err = computeError(positions, positions_ref)
    
    return err


def callback(xk,planet_name,input_file,nb_steps,freq,timestep):
        """
        Append to the history vector the iterations and the function evaluation at each step.
        Parameters
        ----------
        xk : numpy array
            Partial iterations.
        Returns
        -------
        None.
        """
        history.append(np.transpose(np.r_[xk, runAndComputeError(xk,planet_name,input_file,nb_steps,freq,timestep)]))
            
callback_lambda = lambda x: callback(x,planet_name,filename,nb_steps,freq,timestep)

def optimiser(planet_name,input_file,nb_steps,freq,timestep):
    x0 = 1
    history.append(np.transpose(np.r_[x0, runAndComputeError(x0,planet_name,input_file,nb_steps,freq,timestep)]))
    scaling_factor = soo.fmin(runAndComputeError, x0, args=(planet_name,input_file,nb_steps,freq,timestep), callback = callback_lambda)
    print('The scaling factor is equal to ' + scaling_factor)
    return scaling_factor

def plot(history):
    fig = plt.figure()
    fig.plot(history[:,0], history[:,1])
    fig.set_xlabel('scale', fontsize=8)
    fig.set_ylabel('error', fontsize=8)
    plt.title('Scipy optimisation', fontsize=12)
    fig.savefig('optimization.pdf', format='pdf')   
          
if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Particles code optimiser')
    parser.add_argument('filename', type=str,
                        help='start/input filename',
                        default = '../init.csv')
    parser.add_argument('nb_steps', type=int,
                        help='specify the number of steps to perform',
                        default = 365)
    parser.add_argument('freq', type=int,
                        help='specify the frequency for dumps',
                        default = 1)
    parser.add_argument('timestep', type=float,
                        help='timestep',
                        default = 1)
    parser.add_argument('planet_name', type=str,
                        help='name of planet to correct',
                        default = 'mercury')
    


    args = parser.parse_args()
    nb_steps = args.nb_steps
    freq = args.freq
    filename = args.filename
    timestep = args.timestep
    planet_name = args.planet_name
    history = []
    optimiser(planet_name,filename,nb_steps,freq,timestep)
    plot()

filename=  '../init.csv'
nb_steps = 365
freq = 1
timestep = 1
planet_name = 'mercury'



input_df = pd.read_csv(filename, sep = '\s',header=0,engine='python')
input_df.loc[input_df.name == planet_name, ['VX','VY','VZ']] *= scale
input_df.to_csv(output_filename,header=True,index_label = False, sep = ' ')