#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

auto readfile(string filename){
    ifstream  data(filename);
    double *d = new double[6];
    double *e = new double[6];
    int d_val;
    int e_val;
    string line;
    int i = 0;
    while(getline(data,line))
    {
        i ++; 
        stringstream  lineStream(line);
        string        cell;
        d[i] = d_val;
        e[i] = e_val;

    }
    int n = i;
    return d, e, n;
}

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

int main(int argc, char *argv[]){
    /*get input from command line:
    n = number of columns in A and
    d = value of diagonal elements.
    */
    //int n = readfile("dataread.csv")[2];
    double *d = new double[6];
    //d = readfile("dataread.csv")[0];
    double *e = new double[6];
    //e = readfile("dataread.csv")[1];
    int n;
    d, e, n = readfile("dataread.csv");


    //Allocating memory for arrays
    double *x = new double[n+1];
    double *rhs = new double[n+1]; // original right hand side: source function
    double *rhs_tilde = new double[n+1]; // original right hand side: source function
    double *d_tilde = new double[n+1];
    double *v_num = new double[n+1];
    double *u_exact = new double[n+1];
    //Fill arrays
    x[0] = 0;
    x[-1] = 1;
    double h = (double) (x[1]-x[0])/(n-1);
    double hh = h*h;

    // Initialize
    d_tilde[0] = d[0];
    d_tilde[n] = d[n];
    rhs_tilde[0] = rhs[0];
    v_num[0] = v_num[n] = 0.0;
    for (int i = 0; i<n; i++){
        x[i] = i*h;
        rhs[i] = f(x[i])*hh;
        u_exact[i] = exact(i*h);
      }

    //Foward substitution:
    for (int j = 1; j < n; j++){
        d_tilde[j] = d[j] - e[j-1]*e[j-1]/d_tilde[j-1];
        rhs_tilde[j] = rhs[j] - e[j-1]*rhs_tilde[j-1]/d_tilde[j-1];
    }

    //Backward substitution:
    v_num[n-1] = rhs[n-1]/d_tilde[n-1];
    for (int k = n-2; k > 0 ; k--){
        v_num[k-1] = (rhs_tilde[k-1]-e[k-1]*v_num[k])/d_tilde[k-1];
    }

    //Write to file
    ofstream solutionfile;
  solutionfile.open("Results/simplesolution.csv");
  solutionfile << "step_size," << setw(20) << "x," << setw(20) << "v_num," << setw(20)
              << "u_exact," <<  "\n"<< endl;
  for (int i = 0; i < n; ++i){
          solutionfile << h << ',' << setw(20)  <<x[i] <<',' << setw(20) <<
          v_num[i] << ','<< setw(20) << u_exact[i] << ','<<"\n"<<endl;
        }
    solutionfile.close();

    delete[] x;
    delete[] d_tilde;
    delete[] rhs;
    delete[] rhs_tilde;
    delete[] e;
    delete[] v_num;
    delete[] u_exact;
    return 0;
}