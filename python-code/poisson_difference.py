### Python code for project 1c: Specific solution for the 1D poission equation ###
import numpy as np  # array operations

def initializer(a,b,d_val,e_val, n):
    """
    Function that initializes arrays and source
    Input:
    - a, b: solution interval for x param
    - func: source function
    - d_val: Diagonal element values
    - e_val: Non-diagonal value elements
    - n: points
    """
    h_step = (b-a)/(n-1)
    d = np.full((n,1),d_val, dtype = float); # diagonal (2)
    e = np.full((n,1),e_val, dtype = float); e[n-1] = 0;  # non-diagonal (-1)
    x = np.linspace(a,b,n)
    rhs = (h_step**2)*100*np.exp(-10*x) # do something with this to make array: Use symbolic python
    u_exact = 1-(1-np.exp(-10))*x-np.exp(-10*x)
    return d, e, rhs, u_exact, x

def forward_sbst(d,rhs,n):
    """
    Calculates forward substitution
    for tridiagonal matrix only
    Input:
    - d: diagonal elements (array)
    - rhs: source (array)
    """
    for i in range(1,n):
        d[i] = (i + 1)/i
        rhs[i] = rhs[i] + (i-1)/i*rhs[i-1]
    return d, rhs

def backward_sbtst(u,d,f,n):
    """
    Calculates backward substition
    for tridiagonal matrix only
    Input:
    - u: an array with known endpoints
    - d: diagonal array changed by forward_sbst
    - f: source function altered by forward_sbstn
    - n: number of points in array
    """
    for i in range(n-2,1,-1): # n points, index n-1 last
        u[i-1] = (i-1)/i*(f[i-1] + u[i])
    u[n-1] = f[n-1]/d[n-1]

    return u


#    h_step = (b-a)/(n-1); # not necessary (could have been useful in for loop)
