# FYS4150-Project1
Git for Project 1 in Computational Physics (FYS4150): Finite difference schemes (central difference) to solve a 1D Poisson equation.

Folders: Overview of programs and their functionality:

* Report:
The PDF-version of FYS4150: Project 1 and problem description
        
* python-code: A functional draft of the algorithms to be used in cpp synta

       poisson_difference.py implements the simple Thomas algorithm tailored for the specific central difference scheme
    
   
       main_triagonal.py calls the functions and plots the results of numerical and analytical solution

* cpp-code: The main code in cpp syntax

   - Data: Could be used in an improved version of the programmes to read off a matrix into general_solver.cpp
   
  - Results: Results written to file, including figures (own folder)
  
        general_solver.cpp solves the Poisson equation using a general Thomas algorithm.
  
        lu_arma.cpp  solves the differential equation by use of armadillo library LU-decomposition
        
        lu_eigen.cpp solves the differential equation by use of eigen library LU-decomposition
        
        simple_solver.cpp solves the d.e. using a tailored Thomas algorithm.
        
        simple_solvertest.cpp tests the simple Thomas algorithm solution, by making use of quadratic exact numerical solution.
        
