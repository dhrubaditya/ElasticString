#ifndef FILE_ESTRING_SEEN
#define FILE_ESTRING_SEEN
/*---------------------------------------*/
#include<math.h>
using namespace std;
/* ----------------------------------------*/
unsigned int const Np=20;				// total number of points on the rod.
unsigned int const pdim=3*Np; 
double const AA = 0.001;		  		// AA is bending rigidity constant (AA = EI), unit -> Pa.m^4
double const aa =  1.0/(double)(Np); 	// distance between two nodes.
                                        //which should be constant accodrding to the constraint.
double const HH = 16*AA/(aa*aa);		// H should be atleast 1500 times of A. Follow: bit.ly/2r23lmA unit -> Pa.m^2
// double const HH = 0.;
double const Gamma=1.;
double const Z0=0.;
double const FFZ0 = 0.1;				// Force Value on the ends
double const omega = 0.02;
/* ----------------------------------------*/
void iniconf(double *y);
void diagnos(double time, int itn, double y[]);
/* ----------------------------------------*/
#endif /* !FILE_ESTRING_SEEN */
