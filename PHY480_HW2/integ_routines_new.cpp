//  file: integ_routines_new.cpp
//
//  These are routines for Simpson and Milne rules
//                                                                     
//  Programmer:  Dylan Smith
//
// 
//************************************************************************

// include files
#include <cmath>
#include "integ_routines_new.h"   // integration routine prototypes

//************************************************************************

// Integration using Simpson's rule
double simpsons_rule ( int num_pts, double x_min, double x_max,
                      double (*integrand) (double x) )
{
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero
   
   for (int n=2; n<num_pts; n+=2)                // loop for odd points
   {
     double x = x_min + interval * double(n-1);
     sum += (4./3.)*interval * integrand(x);
   }
   for (int n=3; n<num_pts; n+=2)                // loop for even points
   {
     double x = x_min + interval * double(n-1);
     sum += (2./3.)*interval * integrand(x);
   }
   // add in the endpoint contributions
   sum +=  (interval/3.) * (integrand(x_min) + integrand(x_max));
   
   return (sum);
}

//***************************************************************
//Milne Rule
double milne_rule ( int num_pts, double x_min, double x_max,
                      double (*integrand) (double x) )
{
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero
   
   for (int n=2; n<num_pts; n+=4)
   {
     double x = x_min + interval * double(n-1);
     sum += (64./45.)*interval * integrand(x);
   }
   for (int n=3; n<num_pts; n+=4)
   {
     double x = x_min + interval * double(n-1);
     sum += (24./45.)*interval * integrand(x);
   }
    for (int n=4; n<num_pts; n+=4)
    {
      double x = x_min + interval * double(n-1);
      sum += (64./45.)*interval * integrand(x);
    }
    for (int n=5; n<num_pts; n+=4)                // loop for even points
    {
      double x = x_min + interval * double(n-1);
      sum += (28./45.)*interval * integrand(x);
    }
   // add in the endpoint contributions
   sum +=  (14.*interval/45.) * (integrand(x_min) + integrand(x_max));
   
   return (sum);
}
