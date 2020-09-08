### Code to visualize:
### 1) The exact and numerical solution
### 2) The error

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import argparse

### Read from csv file using panda
def get_elements(filename):
    """
    Create dataframe and get columns as vectors (mesh - arrays)
    """
    df = pd.read_csv(filename)
    af = df.to_numpy()
    adf = af[:,0:5]
    df_step = df.loc[1,"step_size"]
    num_step = df.shape[0]
    df_x = df.iloc[:,1]
    x = adf[:,1]
    df_num = df.iloc[:,2]
    numerical = adf[:,2]
    df_exact = df.iloc[:,3]
    exact = adf[:,3]

    return df_step, num_step, x, numerical, exact


def visualize(h, l2,num_step, x,x_s, u_num, u_exact, makeplot = True, save = True):
    """
    Plot the numerical and exact solution
    - input l2 and u_num as array or list/tuple (len 3)
    """
    if makeplot:
        plt.figure()
        plt.title('(h: {:.1e}, n: {:d})\
        $L2/h^2$:({:.2e}, {:.2e},  {:.2e})'.format(h,num_step,l2[0],l2[1],l2[2]), fontsize=12)
        plt.plot(x_s,u_exact,'-', label = 'exact')
        for i in range(len(u_num)):
            nums = ('simple algo','general algo','lu_arma')
            plt.plot(x,u_num[i],'-.',label = nums[i])
            plt.xlabel('x', fontsize=15)
            plt.ylabel('v(x)', fontsize=15)
            plt.legend(fontsize=13)
        if save:
            plt.savefig("figs/diff_{:d}.pdf".format(num_step))
        plt.show()

def rel_error(nn ,u_num, u_exact):
    """
    Computes the relative error.
    Input:
    - n: number of points in numerical solution
    - u_num: Numerical solution
    - u_exact: Exact solution
    """
    n = int(nn)
    rel = np.log10(np.abs((u_num[1:n-1] - u_exact[1:n-1])/u_exact[1:n-1]))
    max_rel = rel.max()
    return abs(max_rel)


def L2(h,num_step,u_num,u_exact): #
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
