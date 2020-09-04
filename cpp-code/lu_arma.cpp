/*
Code for LU-decomposition using library eigen
and writing to file
*/
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <armadillo>

using namespace std;
using namespace arma;

double f(double x){
    /*The right handside of the
    differential equation*/
    return 100*exp(-10*x);
}

double exact(double x){
    /*The analytic solution
    of the differential equation*/
    return 1-(1-exp(-10))*x-exp(-10*x);
}

int main(int argc,char *argv[]){
// Solve for x with lu for specific matrix A given below
int n = atof(argv[1]);
//Allocating memory for arrays
double *x = new double[n+1];
vec rhs(n); // original right hand side: source function
//vec v_num(n);
double *u_exact = new double[n];

//Fill arrays
x[0] = 0;
x[-1] = 1;
double h = (double) (x[-1]-x[0])/(n-1);
double hh = h*h;

// Initialize
for (int i = 0; i<n; i++){
    x[i+1] = i*h;
    rhs(i) = f(x[i+1])*hh;
    u_exact[i] = exact(x[i+1]);
  }


mat A = zeros<mat>(n,n);       // then fill in for the matrix A:
for (int i = 0; i < n; ++i){    //n*n elements,n-1 highest index
    A(i,i) = 2; //diagonal elements
  }
for (int i = 0; i < n-1; ++i){
    A(i+1,i) = -1; // Fill in for elemnts below diag
    A(i,i+1) = -1; // Fill in for elements above diag
  }
cout << A << endl;
/* Now need to find inverse of A, via LU decomposition */
vec v_num  = solve(A,rhs);

//Write to file
cout << v_num << endl;
ofstream solutionfile;
solutionfile.open("Results/lu_solution.csv");
solutionfile << "step_size," << setw(20) << "x," << setw(20) << "v_num," << setw(20)
          << "u_exact," <<  "\n"<< endl;
for (int i = 0; i < n; ++i){
      solutionfile << h << ',' << setw(20)  << x[i+1] <<',' << setw(20) <<
      v_num(i) << ','<< setw(20) << u_exact[i] << ','<<"\n"<<endl;
    }
solutionfile.close();

delete[] x;
delete[] u_exact;

return 0;
}
