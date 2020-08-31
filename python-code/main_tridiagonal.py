###  Runs the specific algorithm for a tridiagonal matrix with same
###  non-diagonal elements

from poisson_difference import initializer, forward_sbst, backward_sbtst
import argparse
import matplotlib.pyplot as plt
import numpy as np

# get input
"""
Note: To use this code you need to add
- a, b: solution interval for x param
- d_val: Diagonal element values
- e_val: Non-diagonal value elements
- n: points
"""
parser = argparse.ArgumentParser() # Creating parser
parser.add_argument('a'); parser.add_argument('b');
parser.add_argument('d_val'); parser.add_argument('e_val')
parser.add_argument('n')
args = parser.parse_args()

# initalize matrix elements
d,e,rhs,u_exact, x = initializer(float(args.a), float(args.b),float(args.d_val),\
                      float(args.e_val),int(args.n))

# Perform forward substitution
d_new, new_rhs = forward_sbst(d,rhs,int(args.n))

# Solve numerically with backward substitution
u = np.zeros(int(args.n)); u[0] = 0; u[int(args.n)-1] = 0;
U_num = backward_sbtst(u,d_new, new_rhs,int(args.n))


# plot numerical and analytical against each other
plt.plot(x,U_num,'--.',label = "numerical")
plt.plot(x,u_exact,'--',label = "exact")
plt.legend()
plt.show()
