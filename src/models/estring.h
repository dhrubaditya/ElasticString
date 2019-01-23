#ifndef FILE_ESTRING_SEEN
#define FILE_ESTRING_SEEN

/**************************/
using namespace std;
/* ----------------------------------------*/
unsigned int const Np= 20;			// total number of points on the rod.
unsigned int const pdim=3*Np;
double const height = 1;					// height of the box we are doing simulations in.
double const aa = height/(double)(Np); 	// distance between two nodes.
// AA = AA/aa ;							// See the equation number 35 in DOI: 10.1063/1.1848511

double const YY = pow(10,5);			// unit -> Pa; it is the Young modulus of the the particular material.
double const dd = 0.005*height;				// r/l ratio for the rod has been kept constant. It should be noted that the particles would also have same diameter.

double const AA = YY*dd*dd*dd*dd*0.05;		 	// AA is bending rigidity constant (AA = EI), unit -> Pa.m^4, 3.14/(16*4) = 0.05

double const viscosity = 10;				// Equivalent to kinematic viscosity of glycerin
double const HH = 16*AA*(1./(dd*dd));		// Follow: bit.ly/2r23lmA unit -> Pa.m^4/m^2 -> Pa.m^2

// The below line is commented because of some error. So I included it in last formulae itself.
// HH =  HH/aa; 			// This is done to model the rod perfectly (Also see: https://goo.gl/nbELSx Week 27/2018 DS)
// double const HH = 0.;

double const OneByGamma=1/(double)height;				// Mobility is just the inverse of Gamma. So OneByGamma is actually the mobility of the system if no
														// back reaction is taken into the account.
double const Z0=0.;						// If we want the bottom point of the rod to be fixed.
// double const FFZ0 = 1*height;		// Force Value on the ends
double const FFZ0 = 0*height*height;					// Different force for different configuration.

double const omega = 0.3;
char const UseRP = 'Y';					// Y is for the new one, O is for old one and N is for not using 
										// Rotne Pragor tensor. 
int const conf_number = 1;
double const ShearRate = 0.2;

char const SaveInfo = 'N';	// This decides whether the simulation is important enough to save the information.
								// Set N for not saving.
/* ----------------------------------------*/
void iniconf(double *y, int conf_number); 	// The § number is defined for different
											// Initial configuration into the system.
void diagnos(double time, int itn, double y[]);
/* ----------------------------------------*/
#endif /* !FILE_ESTRING_SEEN */
