#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>>
#include <chrono>

using namespace std;

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
    /* This provides two options

    1)  Read off csv file to get the arrays
    a, b and c (a: below diagonal, b - diagonal, c
    - above diagonal)

    2) Give specific input for arrays with same valued elements of length n
    */

    int *a_val = new int(0); int *b_val = new int(0);
    int *c_val = new int(0); int *n = new int(0);
    if (argc ==  5){
        cout << "Now solving u for arrays a, b, c with integer elements given in terminal \n"
        << endl;
        int a = atof(argv[1]);
        a_val = &a;                       // Access as global by using pointer
        int b = atof(argv[2]);
        b_val =  &b;
        int c = atof(argv[3]);
        c_val = &c;
        int n_ = atof(argv[4]);
        n = &n_;

  } else if (argc == 3){
        string filename(argv[1]);
        cout << "Reading off" << setw(10) << filename
             << setw(10) << "to get array elements and solve for u \n"
             << endl;

        int n = atof(argv[2]); // Or read off from file Need to use pointer here as well
/* Read off file in folder DATA here: NOT FINISHED!!
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
            cout << n << endl;
*/
  } else {
        cout << "Wrong usage: takes 4 inputs () or 1 (filename)" <<  endl;
        exit(1);
  }

    //Allocating memory for arrays
    double *x = new double[*n+1];
    double *rhs = new double[*n+1]; // original right hand side: source function
    double *v_num = new double[*n+1];
    double *u_exact = new double[*n+1];

    double *b_tilde = new double[*n+1];
    double *a_arr = new double[*n+1];
    double *c_arr = new double[*n+1];

    if (argc == 5){
        for (int i = 0; i<*n; i++){
            b_tilde[i] = *b_val;
            a_arr[i] = *a_val;
            c_arr[i] = *c_val;
        }
      }
    //Fill arrays
    x[0] = 0;
    x[-1] = 1;
    double h = (double) (x[-1]-x[0])/(*n-1);
    double hh = h*h;


    // Initialize
    v_num[0] = v_num[*n] = 0.0;
    for (int i = 0; i<*n; i++){
        x[i] = i*h;
        rhs[i] = f(x[i])*hh;
        u_exact[i] = exact(i*h);
      }

      auto t1 = std::chrono::high_resolution_clock::now(); //  declare start and final time
    //Foward substitution:
    for (int j = 2; j < *n; j++){
        b_tilde[j] = b_tilde[j] - a_arr[j]*c_arr[j-1]/b_tilde[j-1];
        rhs[j] = rhs[j] - a_arr[j]*rhs[j-1]/b_tilde[j-1];
    }

    //Backward substitution:
    v_num[*n-1] = rhs[*n-1]/b_tilde[*n-1];
    for (int k = *n-1; k > 1; k--){
        v_num[k-1] = (rhs[k-1]-c_arr[k-1]*v_num[k])/b_tilde[k-1];
    }

    auto t2 = std::chrono::high_resolution_clock::now(); //get final time
    std::chrono::duration<double, std::milli> time_ms = t2 - t1; //get in milliseconds

    //Write to file

    char *str_full = new char[*n + 30];
    ostringstream size_;
    size_ << *n;
    string num = size_.str(); //make string of solutionsize
    string folder("Results/generalsolution"); //Make string of solution size
    string file_(".csv");
    string adding = folder + num + file_;
    std::size_t length =  adding.copy(str_full,adding.length(),0);
    str_full[length]='\0';
    cout << "Writing to file \n"<< str_full << endl;

    ofstream solutionfile;

  solutionfile.open(str_full);
  solutionfile << "step_size," << setw(20) << "x," << setw(20) << "v_num," << setw(20)
              << "u_exact," << setw(20) << "time"<< "\n"<< endl;
  for (int i = 0; i < *n; ++i){
          solutionfile << h << ',' << setw(20)  << x[i] <<',' << setw(20) <<
          v_num[i] << ','<< setw(20) << u_exact[i] <<
          ',' << setw(20) << time_ms.count() << ',' <<"\n"<<endl;
        }
    solutionfile.close();

    //clean memory
    delete[] a_arr;
    delete[] c_arr;
    delete[] b_tilde;
    delete[] rhs;
    delete[] x;
    delete[] v_num;
    delete[] u_exact;
    return 0;
}
