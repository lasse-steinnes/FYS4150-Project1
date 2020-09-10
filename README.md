# FYS4150-Project1
Git for Project 1 in Computational Physics (FYS4150): Finite difference schemes (central difference) to solve a 1D Poisson equation.

Folders: Overview of programs and their functionality:

* Report: \n
        The PDF-version of FYS4150: Project 1 and problem description \n
        
* python-code: A functional draft of the algorithms to be used in cpp syntax \n
    poisson_difference.py implements the simple Thomas algorithm tailored for the specific central difference scheme \n
    main_triagonal.py calls the functions and plots the results of numerical and analytical solution \n

* cpp-code: The main code in cpp syntax \n

   - Data: Could be used in an improved version of the programmes to read off a matrix into general_solver.cpp \n
   
  - Results: Results written to file, including figures (own folder) \n
  
  - Data: \n
  general_solver.cpp solves the Poisson equation using a general Thomas algorithm.\n
  lu_arma.cpp  solves the differential equation by use of armadillo library LU-decomposition \n
  lu_eigen.cpp solves the differential equation by use of eigen library LU-decomposition \n
  simple_solver.cpp solves the d.e. using a tailored Thomas algorithm.\n 
  simple_solvertest.cpp tests the simple Thomas algorithm solution, by making use of quadratic exact numerical solution.\n
        
