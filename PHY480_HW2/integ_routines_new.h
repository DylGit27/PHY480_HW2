//  file: integ_routines.h
// 
//  Header file for integ_routines_new.cpp
//
//
//  Programmer:  Dylan Smith
//
//************************************************************************

//  begin: function prototypes 
 
extern double simpsons_rule ( int num_pts, double x_min, double x_max,
                       double (*integrand) (double x) );    // Simpson's rule
extern double milne_rule ( int num_pts, double x_min, double x_max,
                       double (*integrand) (double x) );    // Milne's rule

    

//  end: function prototypes 
