//  file: integ_test_new.cpp
// Programmer: Dylan Smith
//
//  Answers to part b and c:
// b) The plot for both the Simpson and Milne Rule error vs N is provided as a log-
// log graph in the repo. Performing a fit for each, Simpson's rule produces a line
// that remains fairly smooth over the whole integration region, with a slope of -4.
// The Milne Rule plot begins linear with a slope of -6, but then decomposes around
// log(N)=5. This is likely due to the relative error being near the machine
// precision.
//
// c) The optimum number of iterations would appear to be 150. This is because 150
// is the lowest error possible before the machine precision causes issues. This is
// backed analytically; we essentially need to solve the equation N^(-6)=10^(-12),
// which yields 100, which is somewhat close to the value from the graph.
// 
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integ_routines_new.h"	// prototypes for integration routines
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
double my_integrand (double x);
double exact_int (double x);

//const double ME = 2.7182818284590452354E0;	// Euler's number

struct my_f_params {double a; double b;};

//GSL Params
double
my_f (double x, void * p )
{
    struct my_f_params * params = (struct my_f_params *)p;
    double a=(params -> a);
    double b=(params -> b);
    
    return a*gsl_asinh(x)+b;
}

//************************************************************************

int
main ()
{
    //GSL function definition
  gsl_function f;
  struct my_f_params params = {1.0,0.0};
  f.function=&my_f;
  f.params=&params;
    
  const gsl_function F=f;
    
  // set up the integration specifiction
  const int max_intervals = 501;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = (exact_int(upper)-exact_int(lower));	// the "exact" answer for the test
  double result = 0.;  // approximate answer

  // open the output file stream
  ofstream integ_out ("integ.dat");	// save data in integ.dat
  integ_out << "#  N     Simpsons      Milne " << endl;
  integ_out << "#-----------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int i = 5; i <= max_intervals; i += 4)
  {
    integ_out << setw(4) << log(i);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log( fabs ((result - answer)/answer));

    result = milne_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log( fabs ((result - answer)/answer));

    integ_out << endl;
  }
    // values to call from GSL function
    double result_gsl;
    double abserr_gsl;
    size_t neval_gsl;
    
    gsl_integration_qng (&F, lower, upper, 0.01, 0.01, &result_gsl, &abserr_gsl, &neval_gsl);
    cout << "GSL Results: " << scientific << result_gsl << "GSL Error: " << abserr_gsl << endl;
  cout << "data stored in integ.dat\n";
  integ_out.close ();

  return (0);
}

//************************************************************************

// the function we want to integrate 
double
my_integrand (double x)
{
  return (asinh(x));
}

// Exact integral solution
double
exact_int (double x)
{
    return ((x*asinh(x))-sqrt(pow(x,2)+1));
}
