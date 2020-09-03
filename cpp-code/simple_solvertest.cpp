/*
Programme to solve the simple case of a poisson equation.
Runs the specific algorithm for a tridiagonal matrix with same
non-diagonal elements in a tridiagonal matrix
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

double f(double x){
    /*The right handside of the
    differential eqation*/
    return 100*exp(-10*x);
}

double exact(double x){
    /*The analytic solution
    of the differential equation*/
    return 1-(1-exp(-10))*x-exp(-10*x);
}

double p(double x){
    /*Alternativ right handside of the
    differential eqation*/
    return 3 + x + 2*x*x;
}

double p_exact(double x){
    /*The analytic solution
    of the alternativ differential equation*/
    return -4 //must make array!
}

double numerical(int a_point, int b_point, int n, int d, double (*f)(double), double (*exact)(double), string filename){
    //Allocating memory for arrays
    double *x = new double[n+1];
    double *rhs = new double[n+1]; // original right hand side: source function
    double *d_tilde = new double[n+1];
    double *v_num = new double[n+1];
    double *u_exact = new double[n+1];
    //Fill arrays
    x[0] = 0;
    x[-1] = 1;
    double h = (double) (b_point-a_point)/(n-1);
    double hh = h*h;
    // Initialize
    d_tilde[0] = d_tilde[n] = 2;
    v_num[0] = v_num[n] = 0.0;
    for (int i = 0; i<n; i++){
        x[i] = i*h;
        rhs[i] = (*f)(x[i])*hh;
        u_exact[i] = exact(i*h);
    }
    //Forward substitution:
    for (int j = 1; j < n; j++){
        d_tilde[j] = (j+1)/double(j);
        rhs[j] = rhs[j] + (j-1)/double(j)*rhs[j-1];
    }
    //Backward substitution:
    v_num[n-1] = rhs[n-1]/d_tilde[n-1];
    for (int k = n-2; k > 0 ; k--){
        v_num[k-1] = (rhs[k-1]+v_num[k])*(k-1)/double(k);
    }
    //Write to file
    ofstream solutionfile;
    solutionfile.open(filename);
    solutionfile << "step_size," << setw(20) << "x," << setw(20) << "v_num," << setw(20)
        << "u_exact," <<  "\n"<< endl;
    for (int i = 0; i < n; ++i){
        solutionfile << h << ',' << setw(20)  <<x[i] <<',' << setw(20) <<
        v_num[i] << ','<< setw(20) << u_exact[i] << ','<<"\n"<<endl;
    }
    solutionfile.close();
    delete[] d_tilde;
    delete[] rhs;
    return x, v_num, u_exact;
    delete[] v_num;
    delete[] x;
    delete[] u_exact;
    }

int main(int argc, char *argv[]){
    /*get input from command line:
    n = number of columns in A and
    d = value of diagonal elements.
    */
    int a_point = atof(argv[1]);
    int b_point = atof(argv[2]);
    int n = atof(argv[3]);
    int d = atof(argv[4]);
    cout<<test_polynomial(a_point, b_point, n, d, p, p_exact, string 'Results/testdata.csv')<<endl;
    double x, double v_num = numerical(int a_point, int b_point, int n, int d, f, exact, string "Results/simplesolution.csv");
    return 0;
}

bool test_polynomial(double a_point, double b_point, int n, int d){
    /*
    Testing the solver with a 2nd order polynomial.
    */
    double x, double test_num, double test_exact = numerical(int a_point, int b_point, int n, int d, p, p_exact, string 'Results/testdata.csv');
    double tol = 1e-14;
    for (int i=0; i<n; i++){
        if (abs(test_num[i]-test_exact[i]) < tol){
            return true;
        }  
        else{
            return false; 
        }
   }
}
    