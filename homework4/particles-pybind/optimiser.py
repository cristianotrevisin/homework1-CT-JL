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


class Optimiser:
    def __init__(self):
        
        parser = argparse.ArgumentParser(description='Particles code optimiser')
        parser.add_argument('filename', type=str, nargs='?',
                            help='start/input filename',
                            default = '../init.csv')
        parser.add_argument('nb_steps', type=int, nargs='?',
                            help='specify the number of steps to perform',
                            default = 365)
        parser.add_argument('freq', type=int, nargs='?',
                            help='specify the frequency for dumps',
                            default = 1)
        parser.add_argument('timestep', type=float, nargs='?',
                            help='timestep',
                            default = 1)
        parser.add_argument('planet_name', type=str, nargs='?',
                            help='name of planet to correct',
                            default = 'mercury')
        args = parser.parse_args()
        
        self.nb_steps = args.nb_steps
        self.freq = args.freq
        self.filename = args.filename
        self.timestep = args.timestep
        self.planet_name = args.planet_name

        
        self.history = []
        
    def readPositions(self,directory):
        filelist = sorted(glob.glob(os.path.join(directory, './step-*.csv')))
        if len(filelist) != 365:
            raise Exception('The length of the input datafile is not 365!')
        trajectory = np.empty((0,3), float)
        for file in filelist:
            a = pd.read_csv(file, sep = '\s',header = None, engine='python')
            if a.iloc[0,0] == '#X':
                a = pd.read_csv(file, sep = '\s',header=0,engine='python')
            planet_position = a[a.iloc[:,-1]==self.planet_name].iloc[:,0:3].to_numpy()
            trajectory = np.append(trajectory, planet_position, axis = 0)
        return trajectory
                
    def computeError(self,positions,positions_ref):
        SSR = 0
        for i in range(365):
            for j in range(3):
                SSR += (positions[i,j]-positions_ref[i,j])**2
        return np.sqrt(SSR)
    
    def generateInput(self,scale,output_filename):
        input_df = pd.read_csv(self.filename, sep = '\s',header=0,engine='python')
        #input_df.loc[input_df.name == planet_name, ['VX','VY','VZ']] *= scale
        row_index = input_df.index.get_loc(input_df.index[input_df['name'] == self.planet_name][0])
        input_df.iloc[row_index,3:6] *= scale
        input_df.to_csv(output_filename,header=True,index_label = False, sep = ' ')
        
    def launchParticles(self):
        PlanetsFactory.getInstance()
        factory = ParticlesFactoryInterface.getInstance()
    
        def createComputes(self):  
            try:
                compute_grav = ComputeGravity()
                compute_verlet = ComputeVerletIntegration(self.timestep)
        
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
        
        evol = factory.createSimulation(self.filename, self.timestep, createComputes)
    
        dumper = CsvWriter("out.csv")
        dumper.write(evol.getSystem())
        
        evol.setNSteps(self.nb_steps)
        evol.setDumpFreq(self.freq)
        evol.evolve()
        
    def runAndComputeError(self,scale):
        output_filename = 'init_scaled.csv'
        self.generateInput(scale,output_filename)
        self.launchParticles()
        positions = self.readPositions(os.getcwd() + '/dumps')
        positions_ref = self.readPositions('../trajectories')
        err = self.computeError(positions, positions_ref)
        
        return err
    
    
    def callback(self,xk):
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
            self.history.append(np.transpose(np.r_[xk, self.runAndComputeError(xk)]))
            #history= np.append(history, [[xk, runAndComputeError(xk,planet_name,input_file,nb_steps,freq,timestep)]], axis = 0)
    
    def optimiser(self):
        x0 = 1
        self.history.append(np.transpose(np.r_[x0, self.runAndComputeError(x0)]))
        #history= np.append(history, [[x0, runAndComputeError(x0,planet_name,input_file,nb_steps,freq,timestep)]], axis = 0)
        scaling_factor = soo.fmin(self.runAndComputeError, x0, callback = self.callback)
        #print('The scaling factor is equal to ' + scaling_factor)
        return scaling_factor
    
    def plot(self):
        history = np.concatenate(self.history).reshape(len(self.history), 2)
        fig = plt.figure()
        plt.plot(history[:,0], history[:,1])
        plt.xlabel('scale', fontsize=8)
        plt.ylabel('error', fontsize=8)
        plt.title('Scipy optimisation', fontsize=12)
        fig.savefig('optimization.pdf', format='pdf')   
          
if __name__ == "__main__":
     opti = Optimiser()
     opti.optimiser()
     opti.plot()