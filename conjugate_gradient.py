"""
    Resolution of Homework 1 part 2 by Cristiano Trevisin and Joseph Lemaitre.
"""

import numpy as np
import scipy.optimize
import matplotlib.pyplot as plt
from matplotlib import cm, rc
import argparse
from mpl_toolkits.mplot3d import Axes3D

class ConjugateGradient:
    """Class to allow resolution of the conjugate gradient."""

    def __init__(self):
        """
        Initialize of the ConjugateGradient class.
        Reads the matrix from the input files and compute the solution of the system
        using the conjugate gradient method.

        Returns
        -------
        None.

        """
        parser = argparse.ArgumentParser(description="Optimizer of a quadratic function S(x)")
        parser.add_argument("--filename", "-f", nargs='?', help="path to file where system Ax=b is stored",
                            default="input.csv", type=str)
        parser.add_argument("--plot", "-p", nargs='?', help="if plot", default="yes", type=str)
        parser.add_argument("--initial_guess", "-g", nargs='?', help="path to file where initual guess x0 is stored",
                            default=None, type=str)
        parser.add_argument("--tolerance", "-t", nargs='?', help="tolerance required", default=1e-9, type=float)
        args = parser.parse_args()
        filename = args.filename
        self.ifplot = args.plot
        d = np.genfromtxt(filename, delimiter=',')

        self.A = d[0:-1, :]
        self.b = d[-1, :]

        if args.initial_guess:
            self.initial_guess = args.initial_guess
            self.x0 = np.genfromtxt(args.initial_guess, delimiter=',')
            self.x0toplot = np.genfromtxt(args.initial_guess, delimiter=',')
        else:
            self.x0 = np.zeros(self.b.shape)
            self.initial_guess = None
            self.x0toplot = np.zeros(self.b.shape)

        self.tol = args.tolerance  # norm tolerance
        self.history = []  # init history vector
        self.check_input()

    def check_input(self):
        """
        Check if the input arguments are correct.

        Raises
        ------
        Exception
            DESCRIPTION.

        Returns
        -------
        None.

        """
        if (np.abs(self.A - self.A.T) > 1e-9).all():
            raise Exception("The matrix A is not symmetric. Cannot execute conjugate gradient method")
        if np.all(np.linalg.eigvals(self.A) < 0):
            raise Exception("The matrix A is not positive definite. Cannot execute conjugate gradient method")
        if self.A.shape[0] != self.A.shape[1]:
            raise Exception("The matrix A is not a square matrix. Check input!")
        if self.A.shape[0] != self.b.shape[0]:
            raise Exception("The matrix A is not compatible with vector b. Check input!")
        if self.initial_guess is not None and self.b.shape != self.x0.shape:
            raise Exception("Initial guess vector is not compatible with the system. Check input!")

    def fun(self, x):
        """
        Evaluate the S(x,y) = x.T @ A @ x - x.T @ b function.
        
        Parameters
        ----------
        x : numpy array
            It represents the main variable of the function S(x)

        Returns
        -------
        float64
            Returns the evaluation of the function.

        """
        return 1 / 2 * np.einsum('i,ik,k', x, self.A, x) - np.einsum('i,i', x, self.b)

    def callback(self, xk):
        """
        Append to the history vector the partial iteration points and their evaluation.

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
        Calculate the residual of the function.

        Parameters
        ----------
        x : numpy array
            Main variable of the function.

        Returns
        -------
        numpy array
            the difference b-Ax.

        """
        return self.b - np.einsum('ik,k', self.A, x)

    def conjgrad(self):
        """
        Minimize the problem iteratively through the Conjugate Gradient method.
        
        The method is based on the algorithm presented in 
        https://en.wikipedia.org/wiki/Conjugate_gradient_method

        Parameters
        ----------
        All parameters are declared in __init__

        Returns
        -------
        xk: numpy array
            root of the system.
        k: int
            number of iterations.
        """
        r = self.residual(self.x0)
        if np.einsum('i,i', r, r) < self.tol:
            self.callback(self.x0)
            return self.x0, 1
        else:
            pk = r
            xk = self.x0

            self.callback(xk)
            for k in range(1, len(self.b)+1):
                alphak = np.einsum('i,i', r, r) / np.einsum('i,ik,k', pk, self.A, pk)
                xk += alphak * pk
                self.callback(xk)

                rkp1 = r - alphak * np.einsum('ik, k', self.A, pk)

                if np.einsum('i,i', rkp1, rkp1) < self.tol:
                    return xk, k

                betak = np.einsum('i,i', rkp1, rkp1) / np.einsum('i,i', r, r)

                pk = betak * pk + rkp1
                r = rkp1

            return xk, k

    def minimizer_tool(self):
        """
        Calculate the roots of the solution Ax = b through the CG method.
        
        To allow comparison between own algorithm and that of scipy.

        Returns
        -------
        res : Dictionary
            res.x is the root of the system
            res.nit is the number of iterations done.

        """
        print("\nMatrix A is \n", self.A)
        print("\nVector b is \n", self.b.T)
        print(f"\nThe built-in algorithm is initialized with tolerance {self.tol} iterations.")
        print("Finding the root of the system Ax = b with the conjugate gradient method...")

        self.history.append(np.transpose(np.r_[self.x0, self.fun(self.x0)]))
        res = scipy.optimize.minimize(self.fun, self.x0, method='CG', callback=self.callback)
        self.history_s = self.history
        self.res_s = res.nit
        self.history = []
        res = DotDict()
        res.x, res.nit = self.conjgrad()
        print('\nSolution found in', res.x)
        return res

    def plot(self, res):
        """
        Plot the conjugate gradient.

        Parameters
        ----------
        res : TYPE
            DESCRIPTION.

        Returns
        -------
        None.

        """
        if self.ifplot == "yes":
            self.history = np.concatenate(self.history).reshape(res.nit + 1, 3)
            self.history_s = np.concatenate(self.history).reshape(self.res_s + 1, 3)
            radius = max(abs(res.x - self.x0toplot)) + 0.5
            x = np.linspace(res.x[0] - radius, res.x[0] + radius, 100)
            y = np.linspace(res.x[1] - radius, res.x[1] + radius, 100)
            z = np.empty((100, 100))
            for indx, valx in np.ndenumerate(x):
                for indy, valy in np.ndenumerate(y):
                    z[indx, indy] = self.fun(np.array([valx, valy]))

            xx, yy = np.meshgrid(x, y)
            fig = plt.figure()
            ax = fig.gca(projection='3d')
            ax.plot_surface(xx, yy, z, cmap=cm.coolwarm,
                            alpha=0.5)
            ax.contour(xx, yy, z, cmap=cm.coolwarm)
            ax.view_init(elev=60., azim=120)
            ax.plot3D(self.history[:, 0], self.history[:, 1], self.history[:, 2], '.--r', label="Own solver")
            ax.plot3D(self.history_s[:, 0], self.history_s[:, 1], self.history_s[:, 2], ':ob', markersize=.5,
                      label="Scipy solver")
            ax.legend()
            ax.grid(False)
            ax.set_xlabel('x', fontsize=8)
            ax.set_ylabel('y', fontsize=8)
            rc('axes', labelsize=10)
            fig.savefig('conjugate_gradient.pdf', format='pdf')


class DotDict(dict):
    """Make dictionaries readable in dot format."""
    pass


if
cg = ConjugateGradient()
res = cg.minimizer_tool()
cg.plot(res)
