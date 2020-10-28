""" 
Plot routines as part of Homework 2 by Cristiano Trevisin and Joseph Lemaitre.
"""

import matplotlib.pyplot as plt
import argparse
import pandas as pd
import numpy as np

def main():
    """
    Prepare the environment for creating the plot of the series.
    
    Loads the series as a dataframe and detect automatically iteration, result
    and error. If there are null values in the error column (i.e. because the 
    analytic prediction was not available in the C++ routines), it only gives 
    the plot of the series.
    
    Takes as arguments: 
        filename of the series calculations; 
        desidered separator in such file;
        output file wanted (if none, it just shows the plot).
    

    Returns
    -------
    None.

    """
    parser = argparse.ArgumentParser(
        description='Plotter of the series convergence')
    parser.add_argument('-f', '--file_name', type=str,
                        help=('file_name where convergence results are stored'), 
                        default = 'example.txt')
    parser.add_argument('-s', '--separator', type=str,
                        help=('separator provided in the file where convergence results are stored'),
                        default = 'space')
    parser.add_argument('-o', '--output_file', type=str,
                        help=('file where the plot is saved'),
                        default = ' ')
    
    args = parser.parse_args()
    file_name = args.file_name
    separator = args.separator
    output_file = args.output_file
    
    # Loads the dataframe
    if separator == 'space':
        data_plot = pd.read_csv(file_name, sep= ' ')
    elif separator == 'tab':
        data_plot = pd.read_csv(file_name, header=True, sep= '\t')
    elif separator == 'comma':
        data_plot = pd.read_csv(file_name, header=True, sep= ',')
    elif separator == 'pipe':
        data_plot = pd.read_csv(file_name, header=True, sep= '|')
    
    # Plots the dataframe
    if data_plot['error'].isnull().values.any():
        fig, axs = plt.subplots(1,1, squeeze=True)
        axs.plot(data_plot['iter'], data_plot['result'])
        axs.set_xlabel('Iteration')
        axs.set_ylabel('Series result')
        axs.legend(["Series"],loc=4)
        axs.grid(True)
    else:
        fig, axs = plt.subplots(2,1,sharex=True, squeeze=True)
        axs[0].plot(data_plot['iter'], data_plot['result'])
        axs[0].hlines(np.pi, 0, data_plot.shape[0], 'r', 'dashed')
        axs[0].set_ylabel('Series result')
        axs[0].grid(True)
        axs[0].legend(["Series", "Exact solution"],loc=4)
        axs[1].plot(data_plot['iter'], data_plot['error'], 'red')
        axs[1].set_ylabel('Series error')
        axs[1].set_xlabel('Iteration')
        axs[1].grid(True)
        
    # Decision whether to save or show the plot.
    if output_file == ' ':
        plt.show()
    else:
        plt.savefig(output_file)
          
if __name__ == "__main__":
    main()