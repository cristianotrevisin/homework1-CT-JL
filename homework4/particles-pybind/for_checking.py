#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan 18 09:33:29 2021

@author: cristiano
"""



import numpy as np
import os
import pandas as pd
import glob


    
def computeError(planet_name):
        """Compute error based on the difference between two trajectories.
        
        Input: trajectories (two 365x3 numpy).
        Output: a float.
        """
        
        def readPositions(planet_name,directory):
            """Read trajectory from dumping folder.
            
            Input: directory where the dumps are stored.
            Output: a numpy with the position with time.
            """
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
        
        positions = readPositions(planet_name, os.getcwd() + '/dumps')
        positions_ref = readPositions(planet_name, '../trajectories')
        SSR = 0
        for i in range(365):
            for j in range(3):
                SSR += (positions[i,j]-positions_ref[i,j])**2
        return np.sqrt(SSR)
    
err_sun = computeError('sun')
err_mer = computeError('mercury')
err_nep = computeError('neptune') 
err_jup = computeError('jupiter') 
err_ura = computeError('uranus')
err_mar = computeError('mars')
err_ear = computeError('earth') 
err_ven = computeError('venus') 
err_sat = computeError('saturn') 