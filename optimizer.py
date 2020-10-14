"""Resolution of Homework 1 part 1 by Cristiano Trevisin and Joseph Lemaitre."""

import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt
from matplotlib import cm, rc
from mpl_toolkits.mplot3d import Axes3D


class Optimizer:
    """Class to find the minimum for the quadratic function S(x) with the BGGS and Conjugate Gradient methods."""

    def __init__(self, method):
        """
        Initialize of the opti class. Specifically, it initializes the history array
        and reads the method to assign to the scipy module.
        
        Returns
        -------
        None.

        """
        self.history = []
        self.method = method

    def fun(self, x):
        """
        Define the function S(x) and evaluate it for a set of (x,y) values.

        Parameters
        ----------
        x : numpy array
            Independent variable of the solution.

        Returns
        -------
        float
            Evaluation of the function.

        """
        A = np.array([[4., 0.],
                      [1., 3.]])
        b = np.array([0., 1.])
        return np.take(x.T @ A @ x - x.T @ b, 0)

    def callback(self, xk):
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
        self.history.append(np.transpose(np.r_[xk, self.fun(xk)]))

    def minimizer_tool(self):
        """
        Initialize the initial guess as a vector of zeros. Run the optimizer algorithm and print to screen the results.

        Returns
        -------
        res : dictionary
            Contains the result of the scipy optimization, including the solution (accessible at res.x)
            and the number of iterations (res.nit).

        """
        x0 = np.ones(2)
        self.history.append(np.transpose(np.r_[x0, self.fun(x0)]))
        res = minimize(self.fun, x0, method=self.method, callback=self.callback)
        print('With method ' + self.method + ":")
        print('solution found in ', res.x)
        print('with ' + str(res.nit) + " iterations. \n")
        return res

    def plot(self, res):
        """
        Plot the result of the optimization and save it to a pdf file.

        Parameters
        ----------
        res : dictionary
            DContains the result of the scipy optimization, including the solution
            (accessible at res.x) and the number of iterations (res.nit).

        Returns
        -------
        None.

        """
        self.history = np.concatenate(self.history).reshape(res.nit + 1, 3)
        x = np.linspace(res.x[0] - 1.5, res.x[0] + 1.5, 100)
        y = np.linspace(res.x[1] - 1.5, res.x[1] + 1.5, 100)
        z = np.empty((100, 100))
        for indx, valx in np.ndenumerate(x):
            for indy, valy in np.ndenumerate(y):
                z[indx, indy] = self.fun(np.array([valx, valy]))

        xx, yy = np.meshgrid(x, y)
        fig = plt.figure()
        ax = fig.gca(projection='3d')
        ax.plot_surface(xx, yy, z, cmap=cm.coolwarm, alpha=0.5)
        ax.contour(xx, yy, z, cmap=cm.coolwarm)
        ax.view_init(elev=60., azim=120)
        ax.plot3D(self.history[:, 0], self.history[:, 1], self.history[:, 2], '.--r')
        ax.grid(False)
        ax.set_xlabel('x', fontsize=8)
        ax.set_ylabel('y', fontsize=8)
        rc('axes', labelsize=10)
        if self.method == "CG":
            methodstring = "Conjugate Gradient"
        else:
            methodstring = self.method
        plt.title(methodstring, fontsize=12)
        fig.savefig('optimization_' + self.method + '.pdf', format='pdf')


# Call method for BFGS algorithm

opti1 = Optimizer("BFGS")
res1 = opti1.minimizer_tool()
opti1.plot(res1)

# Call method for CG algorithm
opti2 = Optimizer("CG")
res2 = opti2.minimizer_tool()
opti2.plot(res2)
