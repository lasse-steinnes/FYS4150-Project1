/*
Code for solving a differential equation using
LU-decomposition with library armadillo
and writing to file
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include <chrono>
#include <sstream>

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
  /* Takes input
  n = number of columns and rows in matrix A
  */
  int n = atof(argv[1]);

//Allocating memory for arrays
double *x = new double[n+1];
vec rhs(n); // original right hand side: source function
//vec v_num(n);
double *u_exact = new double[n];

//Fill arrays
x[0] = 0;
x[n] = 1;
double h = (double) (x[n]-x[0])/(n);
double hh = h*h;

// Initialize
for (int i = 0; i<n; i++){
    x[i] = i*h;
    rhs(i) = f(x[i])*hh;
    u_exact[i] = exact(x[i]);
  }

// Solve for x with lu for specific matrix A given below
mat A = zeros<mat>(n,n);       // fill in for the matrix A:
for (int i = 0; i < n; ++i){    //n*n elements,n-1 highest index
    A(i,i) = 2; //diagonal elements
  }
for (int i = 0; i < n-1; ++i){
    A(i+1,i) = -1; // Fill in for elemnts below diag
    A(i,i+1) = -1; // Fill in for elements above diag
  }
/* Now need to find inverse of A, via LU decomposition */
auto t1 = std::chrono::high_resolution_clock::now(); //  declare start and final time

vec v_num  = solve(A,rhs);

auto t2 = std::chrono::high_resolution_clock::now(); //get final time
std::chrono::duration<double, std::milli> time_ms = t2 - t1; //get in milliseconds

//Write to file
char *str_full = new char[30];
ostringstream size_;
size_ << n;
string num = size_.str(); //make string of solutionsize
string folder("Results/lu_arma");
string file_(".csv");
string adding = folder + num + file_;
std::size_t length =  adding.copy(str_full,adding.length(),0);
str_full[length]='\0';
cout << "Writing to file \n"<< str_full << endl;


ofstream solutionfile;
solutionfile.open(str_full);
solutionfile << "step_size," << setw(20) << "x," << setw(20) << "v_num," << setw(20)
            << "u_exact," << setw(20) << "time,"<< "\n"<< endl;
for (int i = 0; i < n; ++i){
        solutionfile << h << ',' << setw(20)  << x[i] <<',' << setw(20) <<
        v_num(i) << ','<< setw(20) << u_exact[i+1] <<
        ',' << setw(20) << time_ms.count() << ',' <<"\n"<<endl;
      }
  solutionfile.close();
delete[] x;
delete[] u_exact;

return 0;
}
