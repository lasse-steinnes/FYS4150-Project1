//attempting to push:)
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>

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

int main(int argc, char *argv[]){
    /*get input from command line: 
    n = number of columns in A and
    d = value of diagonal elements.
    */
    int n = atof(argv[1]);
    int d = atof(argv[2]);
    //Allocating memory for arrays
    double *x = new double[n+1];
    double *b = new double[n+1];
    double *d_tilde = new double[n+1];
    double *v = new double[n+1];
    double *u = new double[n+1];
    //Fill arrays
    x[0] = 0;
    x[-1] = 1;
    double h = (double) 1/(n+2);
    double hh = h*h;
    d_tilde[0] = d_tilde[n] = 2; v[0] = v[n] = 0.0;
    for (int i = 1; i < n; i++){
        d_tilde[i] = (i+1)/(double) i;
    }
    for (int i = 0; i<n; i++){
        x[i] = i*h;
        b[i] = f(x[i])*hh;
        u[i] = exact(i*h);
    }
    //Foward substitution:
    for (int j = 2; j > n; j++){
        b[j] += b[j-1]/d_tilde[j-1];
    }

    //Backward substitution:
    v[n-1] = b[n-1]/d_tilde[n-1];
    for (int k = n-2; k > 0 ; k--){
        v[k] = (b[k]+v[k+1])/d_tilde[k];
    }
    //Write to file
    ofstream solutionfile;
    solutionfile.open ("simplesolution.txt");
    for (int m = 0; m<sizeof(v)/sizeof(v[0]); m++){
            solutionfile << x[m] << endl;
            solutionfile << v[m] << endl;
    }
    solutionfile.close();
    delete[] x;
    delete[] d_tilde;
    delete[] b;
    delete[] v;
    delete[] u;
    return 0;
}