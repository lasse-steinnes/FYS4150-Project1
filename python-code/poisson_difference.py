### Python code for project 1c: Specific solution for the 1D poission equation ###
import numpy as np

def initializer(a,b, func,d_val,e_val, n):
    h_step = (b-a)/(n+1);
    d = np.full((1,n),d_val, dtype = float); # diagonal (2)
    e = np.full((1,n),e_val, dtype = float); e[n] = 0;  # non-diagonal (-1)
    rhs = func() # do something with this to make array: Use symbolic python
    return

def forward_sbst(d,rhs):
    """
    Calculates forward substitution
    for tridiagonal matrix only
    """
    for i in range(1,n):
        d[i] = (i + 1)/i
        rhs[i] = rhs[i] + (i-1)/i*f[i-1]

def backward_sbtst(u,rhs):
    """
    Calculates backward substition
    for tridiagonal matrix only
    """
    for i in range(n-1,1,-1):
        u[i-1] = (i-1)/i*(rhs[i-1] + u[i])
    u[n] = f[n]/b[n]

    return u
