### Code to visualize:
### 1) The exact and numerical solution
### 2) The error

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import argparse

### Read from csv file using panda
def get_elements(filename):
    '''
    # Creating parser
    parser = argparse.ArgumentParser()
    parser.add_argument('--filename'); args = parser.parse_args();

    # create dataframe and get columns as vectors (mesh - arrays)
    '''
    df = pd.read_csv(filename)
    print(df.head())
    
    df_step = df.iloc[1,"step_size"]; num_step = df_step.to_numpy()
    df_x = df.loc[:,"x"]; x = df_x.to_numpy()
    df_num = df.loc[:,"v_num"]; numerical = df_num.to_numpy()
    df_exact = df.loc[:,"u_exact"]; exact = df_exact.to_numpy()

    return num_step, x, numerical, exact


def visualize(l2,num_step, x, u_num,u_exact, makeplot = True):
    """
    Plot the numerical and exact solution
    """
    if makeplot:
        plt.figure()
        plt.title('Finite Difference solution to Poisson \n (h: {:.5f}, \
                 L2/h**2:{:.5f})'.format(h,l2))
        plt.plot(x,u_num,'--.',label = 'numerical')
        plt.plot(x,u_exact,'--', label = 'exact')
        plt.legend()
        plt.show()

def rel_error(u_num, u_exact):
    """
    Computes the relative error.
    Input:
    - u_num: Numerical solution
    - u_exact: Exact solution
    """
    rel = np.log10(np.abs((u_num[:] - u_exact[:])/u_exact[:]))
    max_rel = rel.max()
    return max_rel


def L2(num_step,u_num,u_exact): #
    """
    Tests the methods stability. Note, a natural extension
    would be to calculate the convergence rate i.e.
    if for each halved h_step, the error
    is reduced by a factor 1/4, so r = 2, or E = C(h)**2
    Function is used in test_convergence
    input:
    - num_step
    - u_num,
    - u_exact
    """
    e = u_num - u_exact # absolute error
    E =  np.sqrt(h*np.sum(e**2)) # Approximation of the L2 norm
    const = E/num_step**2        # Should remain constant with change in step if stable
    return E, const