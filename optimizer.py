#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  8 15:47:31 2020

@author: cristiano
"""

import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt
from matplotlib import cm, rc
from mpl_toolkits import mplot3d


def fun(x):
    A = np.array([[4., 0.], 
                  [1., 3.]])
    b = np.array([0., 1.])
    return np.take(x.T @ A @ x - x.T @ b,0)


def callback(xk):
    history.append(np.transpose(np.r_[xk, fun(xk)]))
 


def minimizer_tool(fun,method):
    x0 = np.array([1., 1.])
    history.append(np.transpose(np.r_[x0, fun(x0)]))
    res = minimize(fun, x0, method=method,callback=callback) 
    return res
    
        
def plot(res, history):
    history = np.concatenate(history).reshape(res.nit+1, 3)
    x = np.linspace(res.x[0]-1,res.x[0]+1,100)
    y = np.linspace(res.x[1]-1,res.x[1]+1,100)
    z = np.empty((100,100))
    for indx, valx in np.ndenumerate(x):
        for indy, valy in np.ndenumerate(y):
            z[indx, indy] = fun(np.array([valx,valy]))

    xx,yy = np.meshgrid(x,y)    
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(xx, yy, z, cmap=cm.coolwarm,
                                       alpha = 0.5)
    ax.contour(xx,yy,z,cmap = cm.coolwarm)
    ax.view_init(elev = 60., azim = 120)
    ax.plot3D(history[:,0],history[:,1],history[:,2], '.--r')
    ax.grid(False)
    ax.set_xlabel('x',fontsize = 8)
    ax.set_ylabel('y',fontsize = 8)
    rc('axes', labelsize=10)
    fig.savefig('optimization.pdf',format='pdf')

history = [];
res = minimizer_tool(fun, 'BFGS')
plot(res,history)