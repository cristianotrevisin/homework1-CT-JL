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
import argparse




class cg():
    # DEFINE INPUT ARGUMENTS
    def __init__(self):
        parser = argparse.ArgumentParser(description="Optimizer of a quadratic function S(x)")
        parser.add_argument("--filename", "-f", nargs='?', help="path to file where system Ax=b is stored", default = "input.csv", type=str)
        parser.add_argument("--method", "-m", nargs='?', help="method for optimization: scipy or else", default = "scipy", type=str)
        parser.add_argument("--plot", "-p", nargs='?', help="if plot",default = "yes", type=str)
        args = parser.parse_args()
        filename = args.filename
        self.method = args.method
        self.ifplot = args.plot
        d = np.genfromtxt(filename, delimiter = ',')
        self.A = d[0:-1,:]
        self.b = d[-1,:]
        self.tol = 1e-5                                                        # norm tolerance
        self.itermax = 1000                                                    # max num of iterations
        self.history = []                                                      # init history vector
        
    
    def fun(self, x):
        """
        Evaluates the S(x,y) = x.T @ A @ x - x.T @ b function
        Parameters
        ----------
        x : numpy array
            It represents the main variable of the function S(x)

        Returns
        -------
        float64
            Returns the evaluation of the function.

        """
        return 1/2 * np.einsum('i,ik,k', x, self.A, x) - np.einsum('i,i', x, self.b)
       
    def callback(self, xk):
        """
        Appends to the history vector the partial iteration points and their evaluation

        Parameters
        ----------
        xk : numpy array
            Partial iteration positions.

        Returns
        -------
        None, but appends to the history vector the state.

        """
        self.history.append(np.transpose(np.r_[xk, self.fun(xk)]))
        
    def residual(self, x):
        """
        Calculates the residual of the function

        Parameters
        ----------
        x : numpy array
            Main variable of the function.

        Returns
        -------
        numpy array
            the difference b-Ax.

        """
        return self.b-np.einsum('ik,k', self.A, x)
        
    def conjgrad(self, x0):
        """
        Minimizes the problem iteratively through the Conjugate Gradient method.
        The method is based on the algorithm presented in 
        https://en.wikipedia.org/wiki/Conjugate_gradient_method

        Parameters
        ----------
        x0 : TYPE
            DESCRIPTION.

        Returns
        -------
        TYPE
            DESCRIPTION.
        TYPE
            DESCRIPTION.

        """
        r = self.residual(x0)
        if np.einsum('i,i', r, r) < self.tol:
            self.callback(x0)
            return x0, 1
        else:
            pk = r
            k = 1
            xk = x0
            self.callback(xk)
            while k <= self.itermax:
                alphak = np.einsum('i,i', r, r) / np.einsum('i,ik,k', pk, self.A, pk)
                xk += alphak * pk
                
                self.callback(xk)
                
                rkp1 = r - alphak * np.einsum('ik, k', self.A, pk)
                
                if np.einsum('i,i', rkp1, rkp1) < self.tol:
                    return xk, k
                
                betak = np.einsum('i,i',rkp1, rkp1) / np.einsum('i,i', r, r)
                
                pk = betak * pk + rkp1
                r = rkp1
                k += 1
                
            print ("Maximum iterations exceeded")
            return xk, k
        
    
    def minimizer_tool(self):
        x0 = np.array([1., 1.])
        if self.method == 'scipy':
            self.history.append(np.transpose(np.r_[x0, self.fun(x0)]))
            res = minimize(self.fun, x0, method='CG',callback=self.callback)
        else:
            res = DotDict()
            res.x, res.nit= self.conjgrad(x0)
        print('Minimum found in', res.x)
        return res
            
    def plot(self,res):
        if self.ifplot == "yes":
            self.history = np.concatenate(self.history).reshape(res.nit+1, 3)
            x = np.linspace(res.x[0]-1,res.x[0]+1,100)
            y = np.linspace(res.x[1]-1,res.x[1]+1,100)
            z = np.empty((100,100))
            for indx, valx in np.ndenumerate(x):
                for indy, valy in np.ndenumerate(y):
                    z[indx, indy] = self.fun(np.array([valx,valy]))
        
            xx,yy = np.meshgrid(x,y)    
            fig = plt.figure()
            ax = fig.gca(projection='3d')
            surf = ax.plot_surface(xx, yy, z, cmap=cm.coolwarm,
                                       alpha = 0.5)
            ax.contour(xx,yy,z,cmap = cm.coolwarm)
            ax.view_init(elev = 60., azim = 120)
            ax.plot3D(self.history[:,0],self.history[:,1],self.history[:,2], '.--r')
            ax.grid(False)
            ax.set_xlabel('x',fontsize = 8)
            ax.set_ylabel('y',fontsize = 8)
            rc('axes', labelsize=10)
            fig.savefig('conjugate_gradient.pdf',format='pdf')


class DotDict(dict):
    pass


cg = cg()
res = cg.minimizer_tool()
cg.plot(res)
    
